#include "uengine/application.h"

#include "uengine/assertion.h"
#include "uengine/log.h"
#include "uengine/input.h"
#include "uengine/time.h"
#include "uengine/rendering/gl.h"

#include <GLFW/glfw3.h>

namespace ue 
{
	application* application::_instance = nullptr;

	application::application() : _is_runing(true)
	{
		UE_CORE_ASSERT(_instance == nullptr, "Application allready exists.");
		_instance = this;
		log::init();
		_window = window::create(window_properties("UEngine", 1280, 720));
		_window->on_close += new lambda<void>([this]() { close(); });
		gl::init();
		_imgui_layer = new imgui_layer();
		push_overlay(_imgui_layer);
		UE_CORE_INFO("Welcome to the UEngine!");
	}

	application::~application()
	{
		delete _window;
	}

	void application::run()
	{
		while (_is_runing)
		{
			time::_time = glfwGetTime();
			time::_delta = time::_time - time::_last_frame_time;
			time::_last_frame_time = time::_time;

			input::mouse_delta = input::get_mouse_position() - input::last_mouse_position;
			input::last_mouse_position = input::get_mouse_position();

			on_update();

			for (auto layer : _layers_stack)
				layer->on_update();

			_imgui_layer->begin();
			on_gui();
			for (auto layer : _layers_stack)
				layer->on_gui();
			_imgui_layer->end();

			_window->on_update();
		}
	}

	void application::close()
	{
		_is_runing = false;
	}
}