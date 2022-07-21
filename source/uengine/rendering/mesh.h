#pragma once

#include "graphics_buffer.h"
#include "vertex_buffer_layout.h"
#include "uengine/core/assertion.h"

#include <glad/glad.h>

namespace ue {
	enum class index_format {
		uint8,
		uint16,
		uint32,
	};

	static GLenum vertex_attribute_format_to_opengl_enum(vertex_attribute_format format) {
		switch (format) {
			case vertex_attribute_format::float16: return GL_HALF_FLOAT;
			case vertex_attribute_format::float32: return GL_FLOAT;
			case vertex_attribute_format::int8: return GL_BYTE;
			case vertex_attribute_format::int16: return GL_SHORT;
			case vertex_attribute_format::int32: return GL_INT;
			case vertex_attribute_format::uint8: return GL_UNSIGNED_BYTE;
			case vertex_attribute_format::uint16: return GL_UNSIGNED_SHORT;
			case vertex_attribute_format::uint32: return GL_UNSIGNED_INT;
		}

		UE_CORE_ASSERT(false, "Unknown format.");
		return 0;
	}

	class mesh {
	public:
		mesh() {
			glGenVertexArrays(1, &_id);
		}

		~mesh() {
			glDeleteVertexArrays(1, &_id);
		}

		static reference<mesh> create() { return reference<mesh>(new mesh()); }

		const reference<graphics_buffer>& get_vertex_buffer(uint32 index) const { return _vertex_buffers[index]; }

		void set_vertex_buffer_params(uint32 count, const vertex_buffer_layout& layout) {
			_layout = layout;
			if (_vertex_buffers.size() == 0)
				_vertex_buffers.push_back(reference<graphics_buffer>());
			bind();
			for (auto& buffer : _vertex_buffers) {
				buffer = reference<graphics_buffer>(
					new graphics_buffer(graphics_buffer::target::vertex, count, _layout.get_stride()));
				buffer->bind();
				uint32 index = 0;
				uint32 offset = 0;
				for (const auto& element : _layout) {
					glVertexAttribPointer(index,
						element.dimension,
						vertex_attribute_format_to_opengl_enum(element.format),
						GL_FALSE,
						_layout.get_stride(),
						reinterpret_cast<const void*>(offset));
					glEnableVertexAttribArray(index);
					offset += element.get_size();
					index++;
				}
			}
		}

		void set_vertex_buffer_data(const void* value, uint32 stream = 0) {
			bind();
			_vertex_buffers[stream]->bind();
			_vertex_buffers[stream]->set_data(value);
		}

		index_format get_index_format() const { return _index_format; }

		const reference<graphics_buffer>& get_index_buffer() const { return _index_buffer; }

		void set_index_buffer_params(uint32 count, index_format format = index_format::uint32) {
			_index_format = format;
			uint32 stride = 0;
			switch (_index_format) {
				case index_format::uint16: {
					stride = sizeof(uint16);
					break;
				}
				case index_format::uint32: {
					stride = sizeof(uint32);
					break;
				}
			}
			bind();
			_index_buffer = reference<graphics_buffer>(
				new graphics_buffer(graphics_buffer::target::index, count, stride));
			_index_buffer->bind();
		}

		void set_index_buffer_data(const void* value) {
			bind();
			_index_buffer->bind();
			_index_buffer->set_data(value);
		}

		void bind() const {
			glBindVertexArray(_id);
		}

		void unbind() const {
			glBindVertexArray(0);
		}
	private:
		uint32 _id;
		vertex_buffer_layout _layout;
		std::vector<reference<graphics_buffer>> _vertex_buffers;
		index_format _index_format = index_format::uint32;
		reference<graphics_buffer> _index_buffer;
	};
}