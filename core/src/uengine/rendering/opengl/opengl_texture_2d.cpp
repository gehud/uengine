#include "uengine/rendering/opengl/opengl_texture_2d.h"

#include "uengine/assertion.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace ue 
{
	opengl_texture_2d::opengl_texture_2d(const char* path)
	{
		int width, height, channels;
		stbi_uc* data = stbi_load(path, &width, &height, &channels, NULL);
		UE_CORE_ASSERT(data, "Failed to load image.");
		_width = width;
		_height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		UE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &_id);
		glTextureStorage2D(_id, 1, internalFormat, _width, _height);

		set_wrap_mode(texture_wrap_mode::repeat);

		set_filter_mode(texture_filter_mode::linear);

		glTextureSubImage2D(_id, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	opengl_texture_2d::~opengl_texture_2d()
	{
		glDeleteTextures(1, &_id);
	}

	void opengl_texture_2d::set_wrap_mode(texture_wrap_mode value)
	{
		_wrap_mode = value;
		switch (_wrap_mode)
		{
		case texture_wrap_mode::repeat:
			glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case texture_wrap_mode::mirror:
			glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			break;
		case texture_wrap_mode::clamp:
			glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		}
	}

	void opengl_texture_2d::set_filter_mode(texture_filter_mode value)
	{
		_filter_mode = value;
		switch (_filter_mode)
		{
		case ue::texture_filter_mode::nearest:
			glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case ue::texture_filter_mode::linear:
			glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		}
	}

	void opengl_texture_2d::bind(int slot) const
	{
		UE_CORE_ASSERT(slot > -1, "Slot index out of range.");
		glBindTextureUnit(slot, _id);
	}
}