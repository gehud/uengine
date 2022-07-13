#pragma once

#include "uengine/core/types.h"
#include "uengine/core/assertion.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace ue {
	enum class texture_format {
		rgb8,
		rgb16,
		rgb32,
		rgba8,
		rgba16,
		rgba32,
	};

	enum class texture_wrap_mode {
		repeat,
		mirror,
		clamp,
	};

	enum class texture_filter_mode {
		nearest,
		linear,
	};

	class texture {
	public:
		virtual uint32 get_width() const = 0;
		virtual uint32 get_height() const = 0;

		virtual texture_wrap_mode get_wrap_mode() const = 0;
		virtual void set_wrap_mode(texture_wrap_mode value) = 0;

		virtual texture_filter_mode get_filter_mode() const = 0;
		virtual void set_filter_mode(texture_filter_mode value) = 0;

		virtual void bind(uint32 slot = 0) const = 0;
	};

	class texture2d : public texture {
	public:
		texture2d(const char* path) {
			int width, height, channels;
			stbi_uc* data = stbi_load(path, &width, &height, &channels, NULL);
			UE_CORE_ASSERT(data, "Failed to load image.");
			_width = width;
			_height = height;

			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4) {
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3) {
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			UE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported.");

			glCreateTextures(GL_TEXTURE_2D, 1, &_id);
			glTextureStorage2D(_id, 1, internalFormat, _width, _height);

			set_wrap_mode(texture_wrap_mode::repeat);

			set_filter_mode(texture_filter_mode::linear);

			glTextureSubImage2D(_id, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}

		~texture2d() {
			glDeleteTextures(1, &_id);
		}

		static reference<texture2d> create(const char* path) { return reference<texture2d>(new texture2d(path)); }

		uint32 get_width() const override { return _width; }
		uint32 get_height() const override { return _height; }

		texture_wrap_mode get_wrap_mode() const override { return _wrap_mode; }
		void set_wrap_mode(texture_wrap_mode value) override {
			_wrap_mode = value;
			switch (_wrap_mode) {
				case texture_wrap_mode::repeat: {
					glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
					break;
				}
				case texture_wrap_mode::mirror: {
					glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
					glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
					break;
				}
				case texture_wrap_mode::clamp: {
					glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					break;
				}
			}
		}

		texture_filter_mode get_filter_mode() const override { return _filter_mode; }
		void set_filter_mode(texture_filter_mode value) override {
			_filter_mode = value;
			switch (_filter_mode) {
				case texture_filter_mode::nearest: {
					glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					break;
				}
				case texture_filter_mode::linear: {
					glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					break;
				}
			}
		}

		void bind(uint32 slot) const override {
			glBindTextureUnit(slot, _id);
		}
	private:
		uint32 _id;
		uint32 _width, _height;
		texture_wrap_mode _wrap_mode;
		texture_filter_mode _filter_mode;
	};
}