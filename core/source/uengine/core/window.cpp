#include "window.h"

#include "log.h"
#include "input.h"
#include "assertion.h"

namespace ue {
	window* window::_instance = nullptr;

	static bool _is_glfw_initialized = false;

	static window* get_window_from_user_ptr(GLFWwindow* handle) {
		return static_cast<ue::window*>(glfwGetWindowUserPointer(handle));
	}

	window::window(uint32 width, uint32 height, const char* title) 
		: _width(width), _height(height), _title(title) {
		UE_CORE_ASSERT(_instance == nullptr, "Window allready exists.");
		_instance = this;

		UE_CORE_LOG_INFO("Creating window: \"{0}\" ({1}, {2})", _title, _width, _height);

		if (!_is_glfw_initialized) {
			int glfw_status = glfwInit();
			UE_CORE_ASSERT(glfw_status, "Could not initialize GLFW.");
			glfwSetErrorCallback([](int error, const char* message) {
				UE_CORE_LOG_ERROR("GLFW Error ({0}): {1}.", error, message);
			});
			_is_glfw_initialized = true;
		}

		_handle = glfwCreateWindow(static_cast<int>(_width), static_cast<int>(_height),
			_title, nullptr, nullptr);

		glfwSetWindowUserPointer(_handle, this);

		glfwSetWindowSizeCallback(_handle, [](GLFWwindow* handle, int width, int height) {
			ue::window* window = get_window_from_user_ptr(handle);
			window->_width = width;
			window->_height = height;
			window->invoke_resize_event(window->_width, window->_height);
		});

		glfwSetWindowCloseCallback(_handle, [](GLFWwindow* handle) {
			ue::window* window = get_window_from_user_ptr(handle);
			window->invoke_close_event();
		});

		glfwSetKeyCallback(_handle, [](GLFWwindow* window, int key, int scanmode, int action, int mods) {
			switch (action) {
				case GLFW_PRESS: {
					input::invoke_key_pressed_event(key, 0);
					break;
				}
				case GLFW_REPEAT: {
					input::invoke_key_pressed_event(key, 1);
					break;
				}
				case GLFW_RELEASE: {
					input::invoke_key_released_event(key);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(_handle, [](GLFWwindow* window, int button, int action, int mods) {
			switch (action) {
				case GLFW_PRESS: {
					input::invoke_mouse_button_pressed_event(button);
					break;
				}
				case GLFW_RELEASE: {
					input::invoke_mouse_button_released_event(button);
					break;
				}
			}
		});

		glfwSetScrollCallback(_handle, [](GLFWwindow* window, double offset_x, double offset_y) {
			input::invoke_mouse_scrolled_event(static_cast<float>(offset_x), static_cast<float>(offset_y));
		});

		glfwSetCursorPosCallback(_handle, [](GLFWwindow* window, double position_x, double position_y) {
			input::invoke_mouse_moved_event(static_cast<float>(position_x), static_cast<float>(position_y));
		});
	}

	window::~window()
	{
		glfwDestroyWindow(_handle);
	}

	void window::set_vsync(bool value)
	{
		_vsync = value;
		if (_vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void window::update() const
	{
		glfwPollEvents();
		glfwSwapBuffers(_handle);
	}
}