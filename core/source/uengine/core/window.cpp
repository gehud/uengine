#include "window.h"

#include "log.h"
#include "assertion.h"

namespace ue {
	window* window::_instance = nullptr;

	static bool _is_glfw_initialized = false;

	window::window(uint32 width, uint32 height, const char* title) 
		: _width(width), _height(height), _title(title) {
		UE_CORE_ASSERT(_instance == nullptr, "Window allready exists.");
		_instance = this;

		UE_CORE_LOG_INFO("Creating window: \"{0}\" ({1}, {2})", _title, _width, _height);

		if (!_is_glfw_initialized) {
			int glfw_init_status = glfwInit();
			UE_CORE_ASSERT(glfw_init_status, "Could not initialize GLFW.");
			glfwSetErrorCallback([](int error, const char* message) {
				UE_CORE_LOG_ERROR("GLFW Error ({0}): {1}.", error, message);
			});
			_is_glfw_initialized = true;
		}

		_handle = glfwCreateWindow(static_cast<int>(_width), static_cast<int>(_height),
			_title, nullptr, nullptr);

		glfwMakeContextCurrent(_handle);

		set_vsync(true);

		glfwSetWindowUserPointer(_handle, this);
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