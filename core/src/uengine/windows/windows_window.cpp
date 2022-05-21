#include "uengine/windows/windows_window.h"

#include "uengine/log.h"
#include "uengine/assertion.h"

#include <GLFW/glfw3.h>

namespace ue 
{
	static bool is_glfw_initialized = false;

	windows_window::windows_window(const window_properties& properties)
		: _title(properties.title), _width(properties.width), _height(properties.height)
	{
		UE_CORE_INFO("Creating window: \"{0}\" ({1}, {2})", _title, _width, _height);

		if (!is_glfw_initialized) 
		{
			int glfwInitStatus = glfwInit();
			UE_CORE_ASSERT(glfwInitStatus, "Could not initialize GLFW.");
			glfwSetErrorCallback([](int error, const char* message)
				{
					UE_CORE_ERROR("GLFW Error ({0}): {1}", error, message);
				});
			is_glfw_initialized = true;
		}

		_window = glfwCreateWindow(static_cast<int>(_width), static_cast<int>(_height),
			_title, nullptr, nullptr);

		glfwMakeContextCurrent(_window);

		glfwSetWindowUserPointer(_window, this);

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) 
		{
			windows_window* this_window = static_cast<windows_window*>(glfwGetWindowUserPointer(window));
			this_window->_width = static_cast<unsigned int>(width);
			this_window->_height = static_cast<unsigned int>(height);
			this_window->invoke_resize_event(this_window->_width, this_window->_height);
		});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) 
		{
			windows_window* this_window = static_cast<windows_window*>(glfwGetWindowUserPointer(window));
			this_window->invoke_close_event();
		});
	}

	windows_window::~windows_window()
	{
		glfwDestroyWindow(_window);
	}

	void windows_window::set_vsync(bool value)
	{
		_is_vsync = value;
		if (_is_vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void windows_window::on_update() const
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}
}