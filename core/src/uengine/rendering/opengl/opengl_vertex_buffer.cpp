#include "uengine/rendering/opengl/opengl_vertex_buffer.h"

#include <glad/glad.h>

namespace ue 
{
	static GLenum vertex_attribute_format_to_opengl_enum(vertex_attribute_format format) 
	{
		switch (format)
		{
			case vertex_attribute_format::bool1:	return GL_BOOL;
			case vertex_attribute_format::int1:		return GL_INT;
			case vertex_attribute_format::int2:		return GL_INT;
			case vertex_attribute_format::int3:		return GL_INT;
			case vertex_attribute_format::int4:		return GL_INT;
			case vertex_attribute_format::float1:	return GL_FLOAT;
			case vertex_attribute_format::float2:	return GL_FLOAT;
			case vertex_attribute_format::float3:	return GL_FLOAT;
			case vertex_attribute_format::float4:	return GL_FLOAT;
			case vertex_attribute_format::mat3:		return GL_FLOAT;
			case vertex_attribute_format::mat4:		return GL_FLOAT;
		}
	}

	opengl_vertex_buffer::opengl_vertex_buffer(const void* data, int count, int stride)
	{
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		UE_CORE_ASSERT(stride >= 0, "Stride out of range.");
		glCreateBuffers(1, &_id);
		bind();
		glBufferData(GL_ARRAY_BUFFER, count * stride, data, GL_STATIC_DRAW);
		_count = count;
		_stride = stride;
	}

	opengl_vertex_buffer::~opengl_vertex_buffer()
	{
		glDeleteBuffers(1, &_id);
	}

	void opengl_vertex_buffer::set_layout(const vertex_buffer_layout& value)
	{
		_layout = value;
		unsigned int index = 0;
		for (const auto& element : _layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.get_dimension(),
				vertex_attribute_format_to_opengl_enum(element.get_format()),
				element.is_normalized() ? GL_TRUE : GL_FALSE,
				_layout.get_stride(),
				(const void*)element.get_offet());
			index++;
		}
	}

	void opengl_vertex_buffer::set_data(const void* data)
	{
		glBufferData(GL_ARRAY_BUFFER, _count * _stride, data, GL_STATIC_DRAW);
	}

	void opengl_vertex_buffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _id);
	}

	void opengl_vertex_buffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}