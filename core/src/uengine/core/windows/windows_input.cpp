#include "windows_input.h"

#include "uengine/core/application.h"

#include <GLFW/glfw3.h>

namespace ue 
{
	bool windows_input::is_key_pressed_impl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool windows_input::is_mouse_button_pressed_impl(int button)
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 windows_input::get_mouse_position_impl()
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return glm::vec2(static_cast<float>(x), static_cast<float>(y));
	}
}