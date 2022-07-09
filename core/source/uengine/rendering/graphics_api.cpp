#include "graphics_api.h"

#include "uengine/core/window.h"
#include "uengine/core/assertion.h"

#include <glad/glad.h>

namespace ue {
	graphics_api::graphics_api() {
		GLFWwindow* window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
		glfwMakeContextCurrent(window);
		int gl_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UE_CORE_ASSERT(gl_status, "Failed to initialize OpenGL.");
		UE_CORE_LOG_INFO("OpenGL Info:");
		UE_CORE_LOG_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		UE_CORE_LOG_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		UE_CORE_LOG_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	graphics_api::~graphics_api() {
		glfwTerminate();
	}
}