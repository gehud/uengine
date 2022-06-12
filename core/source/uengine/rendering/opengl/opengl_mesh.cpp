#include "uengine/rendering/opengl/opengl_mesh.h"

#include "uengine/core/assertion.h"

#include <glad/glad.h>

namespace ue 
{
	static GLenum vertex_attribute_format_to_opengl_enum(vertex_attribute_format format)
	{
		switch (format)
		{
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

	opengl_mesh::opengl_mesh()
	{
		glCreateVertexArrays(1, &_id);
	}

	opengl_mesh::~opengl_mesh()
	{
		glDeleteVertexArrays(1, &_id);
	}

	void opengl_mesh::set_vertex_buffer_params(int count, const vertex_buffer_layout& layout)
	{
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		_vertex_buffer_layout = layout;
		if (_vertex_buffers.size() == 0)
			_vertex_buffers.push_back(reference<graphics_buffer>());
		bind();
		for (auto& buffer : _vertex_buffers) 
		{
			buffer = graphics_buffer::create(graphics_buffer::target::vertex, count, _vertex_buffer_layout.get_stride());
			buffer->bind();
			unsigned int index = 0;
			int offset = 0;
			for (const auto& element : _vertex_buffer_layout)
			{
				glEnableVertexAttribArray(index);
	#pragma warning(push)
	#pragma warning(disable: 4312)
				glVertexAttribPointer(index,
					element.dimension,
					vertex_attribute_format_to_opengl_enum(element.format),
					element.normalized ? GL_TRUE : GL_FALSE,
					_vertex_buffer_layout.get_stride(),
					reinterpret_cast<const void*>(offset));
	#pragma warning(pop)
				offset += element.get_size();
				index++;
			}
		}
	}

	void opengl_mesh::set_vertex_buffer_data(const void* value, int index)
	{
		UE_CORE_ASSERT(index >= 0, "Stream out of range.");
		bind();
		_vertex_buffers[index]->bind();
		_vertex_buffers[index]->set_data(value);
	}

	void opengl_mesh::set_index_buffer_params(int count, index_format format)
	{
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		_index_format = format;
		int stride = 0;
		switch (_index_format)
		{
		case ue::index_format::uint16:
			stride = sizeof(unsigned short);
			break;
		case ue::index_format::uint32:
			stride = sizeof(unsigned int);
			break;
		}
		bind();
		_index_buffer = graphics_buffer::create(graphics_buffer::target::index, count, stride);
		_index_buffer->bind();
	}

	void opengl_mesh::set_index_buffer_data(const void* value)
	{
		bind();
		_index_buffer->bind();
		_index_buffer->set_data(value);
	}

	void opengl_mesh::bind() const
	{
		glBindVertexArray(_id);
	}

	void opengl_mesh::unbind() const
	{
		glBindVertexArray(0);
	}
}