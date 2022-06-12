#include "uengine/rendering/opengl/opengl_graphics_buffer.h"

#include "uengine/core/assertion.h"

#include <glad/glad.h>

namespace ue
{
	opengl_graphics_buffer::opengl_graphics_buffer(target target, int count, int stride)
	{
		_target = target;
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		_count = count;
		UE_CORE_ASSERT(stride >= 0, "Stride out of range.");
		_stride = stride;
		glGenBuffers(1, &_id);
	}

	opengl_graphics_buffer::~opengl_graphics_buffer()
	{
		glDeleteBuffers(1, &_id);
	}

	void opengl_graphics_buffer::set_data(const void* value)
	{
		switch (_target)
		{
		case target::vertex:
			glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(_count * _stride), value, GL_STATIC_DRAW);
			return;
		case target::index:
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(_count * _stride), value, GL_STATIC_DRAW);
			return;
		}

		UE_CORE_ASSERT(false, "Unknown graphics buffer target.");
	}

	void opengl_graphics_buffer::bind() const
	{
		switch (_target)
		{
		case target::vertex:
			glBindBuffer(GL_ARRAY_BUFFER, _id);
			return;
		case target::index:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
			return;
		}

		UE_CORE_ASSERT(false, "Unknown graphics buffer target.");
	}

	void opengl_graphics_buffer::unbind() const
	{
		switch (_target)
		{
		case target::vertex:
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			return;
		case target::index:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			return;
		}

		UE_CORE_ASSERT(false, "Unknown graphics buffer target.");
	}
}