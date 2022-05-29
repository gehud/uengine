#include "opengl_graphics_api.h"

#include "uengine/core/assertion.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace ue 
{
	void opengl_graphics_api::init()
	{
		int glad_init_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UE_CORE_ASSERT(glad_init_status, "Failed to initialize OpenGL.");

		UE_CORE_INFO("OpenGL info:");
		UE_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
		UE_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
		UE_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH);
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

	void opengl_graphics_api::draw_elements(int mode, int count, int type)
	{
		UE_CORE_ASSERT(mode == GL_POINT || mode == GL_LINE_STRIP || mode == GL_LINE_LOOP
			|| mode == GL_LINES || mode == GL_LINE_STRIP_ADJACENCY || mode == GL_TRIANGLE_STRIP
			|| mode == GL_TRIANGLE_FAN || mode == GL_TRIANGLES || mode == GL_TRIANGLE_STRIP_ADJACENCY
			|| mode == GL_TRIANGLES_ADJACENCY || mode == GL_PATCHES, "Unknown render mode.");
		UE_CORE_ASSERT(count >= 0, "Count out of range.");
		UE_CORE_ASSERT(type == GL_UNSIGNED_BYTE || type == GL_UNSIGNED_SHORT || type == GL_UNSIGNED_INT,
			"Incorrect index type.");
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