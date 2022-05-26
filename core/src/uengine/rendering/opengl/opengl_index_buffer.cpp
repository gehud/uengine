#include "opengl_index_buffer.h"

#include "uengine/core/assertion.h"

#include <glad/glad.h>

namespace ue 
{
	opengl_index_buffer::opengl_index_buffer(const unsigned char* indices, int count, int stride) 
		: _type(GL_UNSIGNED_BYTE)
	{
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		UE_CORE_ASSERT(stride >= 0, "Stride out of range.");
		glCreateBuffers(1, &_id);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * stride, indices, GL_STATIC_DRAW);
		_count = count;
		_stride = stride;
	}

	opengl_index_buffer::opengl_index_buffer(const unsigned short* indices, int count, int stride)
		: _type(GL_UNSIGNED_SHORT)
	{
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		UE_CORE_ASSERT(stride >= 0, "Stride out of range.");
		glCreateBuffers(1, &_id);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * stride, indices, GL_STATIC_DRAW);
		_count = count;
		_stride = stride;
	}

	opengl_index_buffer::opengl_index_buffer(const unsigned int* indices, int count, int stride)
		: _type(GL_UNSIGNED_INT)
	{
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		UE_CORE_ASSERT(stride >= 0, "Stride out of range.");
		glCreateBuffers(1, &_id);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * stride, indices, GL_STATIC_DRAW);
		_count = count;
		_stride = stride;
	}

	opengl_index_buffer::~opengl_index_buffer()
	{
		glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &_id);
	}

	void opengl_index_buffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}

	void opengl_index_buffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}