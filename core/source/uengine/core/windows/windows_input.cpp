#include "windows_input.h"

#include "uengine/core/application.h"

#include <GLFW/glfw3.h>

namespace ue 
{
	bool windows_input::get_key_down_impl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		static int last_state = GLFW_RELEASE;
		int state = glfwGetKey(window, keycode);
		if (state == GLFW_PRESS && last_state == GLFW_RELEASE)
		{
			last_state = state;
			return true;
		}
		last_state = state;
		return false;
	}

	bool windows_input::get_key_impl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS;
	}

	bool windows_input::get_key_up_impl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		static int last_state = GLFW_RELEASE;
		int state = glfwGetKey(window, keycode);
		if (state == GLFW_RELEASE && last_state == GLFW_PRESS)
		{
			last_state = state;
			return true;
		}
		last_state = state;
		return false;
	}

	bool windows_input::get_mouse_button_down_impl(int button)
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		static int last_state = GLFW_RELEASE;
		int state = glfwGetMouseButton(window, button);
		if (state == GLFW_PRESS && last_state == GLFW_RELEASE)
		{
			last_state = state;
			return true;
		}
		last_state = state;
		return false;
	}

	bool windows_input::get_mouse_button_impl(int button)
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	bool windows_input::get_mouse_button_up_impl(int button)
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		static int last_state = GLFW_RELEASE;
		int state = glfwGetMouseButton(window, button);
		if (state == GLFW_RELEASE && last_state == GLFW_PRESS) 
		{
			last_state = state;
			return true;
		}
		last_state = state;
		return false;
	}

	vector2 windows_input::get_mouse_position_impl()
	{
		auto window = static_cast<GLFWwindow*>(application::get_instance().get_window().get_native_window());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return vector2(static_cast<float>(x), static_cast<float>(y));
	}
}