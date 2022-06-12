#include "opengl_graphics_api.h"

#include "uengine/core/assertion.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace ue 
{
	static bool _opengl_initialized = false;

	void opengl_graphics_api::init()
	{
		if (_opengl_initialized)
			return;

		gladLoadGL();

		int glad_init_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UE_CORE_ASSERT(glad_init_status, "Failed to initialize OpenGL.");

		UE_CORE_INFO("OpenGL info:");
		UE_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
		UE_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
		UE_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		_opengl_initialized = true;
	}

	void opengl_graphics_api::terminate()
	{
		if (!_opengl_initialized)
			return;
	}

	void opengl_graphics_api::clear_color(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void opengl_graphics_api::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int opengl_graphics_api::get_triangles_mode()
	{
		return GL_TRIANGLES;
	}

	void opengl_graphics_api::draw_elements(int mode, int count, index_format format)
	{
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		GLenum type = 0;
		switch (format)
		{
		case index_format::uint8:
			type = GL_UNSIGNED_BYTE;
			break;
		case index_format::uint16:
			type = GL_UNSIGNED_SHORT;
			break;
		case index_format::uint32:
			type = GL_UNSIGNED_INT;
			break;
		}
		glDrawElements(mode, count, type, NULL);
	}

	void opengl_graphics_api::viewport(int x, int y, int width, int height)
	{
		UE_CORE_ASSERT(x > -1, "X out of range.");
		UE_CORE_ASSERT(y > -1, "Y out of range.");
		UE_CORE_ASSERT(width > -1, "Width out of range.");
		UE_CORE_ASSERT(height > -1, "Height out of range.");
		glViewport(x, y, width, height);
	}
}