#include "input.h"

#include "window.h"

#include <glfw/glfw3.h>

namespace ue {
	vector2 input::last_mouse_position = vector2::zero;
	vector2 input::mouse_position = vector2::zero;
	vector2 input::mouse_position_delta = vector2::zero;

	input::key_pressed_event input::on_key_pressed;
	input::key_released_event input::on_key_released;
	input::mouse_botton_event input::on_mouse_button_pressed;
	input::mouse_botton_event input::on_mouse_button_released;
	input::mouse_moved_event input::on_mouse_moved;
	input::mouse_scrolled_event input::on_mouse_scrolled;

	bool input::get_key_down(int key) {
		auto window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
		static int last_state = GLFW_RELEASE;
		int state = glfwGetKey(window, key);
		if (state == GLFW_PRESS && last_state == GLFW_RELEASE) {
			last_state = state;
			return true;
		}
		last_state = state;
		return false;
	}

	bool input::get_key(int key) {
		auto window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
		int state = glfwGetKey(window, key);
		return state == GLFW_PRESS;
	}

	bool input::get_key_up(int key) {
		auto window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
		static int last_state = GLFW_RELEASE;
		int state = glfwGetKey(window, key);
		if (state == GLFW_RELEASE && last_state == GLFW_PRESS) {
			last_state = state;
			return true;
		}
		last_state = state;
		return false;
	}

	bool input::get_mouse_button_down(int button) {
		auto window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
		static int last_state = GLFW_RELEASE;
		int state = glfwGetMouseButton(window, button);
		if (state == GLFW_PRESS && last_state == GLFW_RELEASE) {
			last_state = state;
			return true;
		}
		last_state = state;
		return false;
	}

	bool input::get_mouse_button(int button) {
		auto window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	bool input::get_mouse_button_up(int button) {
		auto window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
		static int last_state = GLFW_RELEASE;
		int state = glfwGetMouseButton(window, button);
		if (state == GLFW_RELEASE && last_state == GLFW_PRESS) {
			last_state = state;
			return true;
		}
		last_state = state;
		return false;
	}

	void input::update() {
		auto window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		mouse_position = vector2(static_cast<float>(x), static_cast<float>(y));
		mouse_position_delta = mouse_position - last_mouse_position;
		last_mouse_position = mouse_position;
	}
}