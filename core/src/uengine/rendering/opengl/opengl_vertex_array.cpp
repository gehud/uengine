#include "uengine/rendering/opengl/opengl_vertex_array.h"

#include <glad/glad.h>

namespace ue 
{
	opengl_vertex_array::opengl_vertex_array()
	{
		glCreateVertexArrays(1, &_id);
	}

	opengl_vertex_array::~opengl_vertex_array()
	{
		glDeleteVertexArrays(1, &_id);
	}

	void opengl_vertex_array::bind() const
	{
		glBindVertexArray(_id);
	}

	void opengl_vertex_array::unbind() const
	{
		glBindVertexArray(0);
	}
}