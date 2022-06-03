#include "application.h"

#include "uengine/core/assertion.h"
#include "uengine/core/log.h"
#include "uengine/core/input.h"
#include "uengine/core/time.h"
#include "uengine/core/scene.h"
#include "uengine/rendering/gl.h"

#include <GLFW/glfw3.h>

namespace ue 
{
	application* application::_instance = nullptr;
	application_platform application::_platform = application_platform::windows;

	application::application() : _is_runing(true)
	{
		UE_CORE_ASSERT(_instance == nullptr, "Application allready exists.");
		_instance = this;
		log::init();
		_window = window::create(window_properties("UEngine", 1280, 720));
		_window->on_close += new lambda<void>([this](){ close(); });
		gl::init();
		_gui_layer = new gui_layer();
		push_overlay(_gui_layer);
		UE_CORE_INFO("Welcome to the UEngine!");
	}

	application::~application()
	{
		gl::terminate();
		for (auto editor : _editors)
			delete editor;
		for (auto system : _systems)
			delete system;
		delete _window;
	}

	void application::run()
	{
		for (auto system : _systems)
			system->on_start();

		while (_is_runing)
		{
			time::_time = glfwGetTime();
			time::_delta = time::_time - time::_last_frame_time;
			time::_last_frame_time = time::_time;

			input::mouse_position = input::get_mouse_position();
			input::mouse_position_delta = input::mouse_position - input::last_mouse_position;
			input::last_mouse_position = input::mouse_position;

			for (auto system : _systems)
				system->on_update();

			on_update();

			for (auto layer : _layers_stack)
				layer->on_update();

			for (auto scene : _scenes)
				scene->on_update();

			_gui_layer->begin();
			on_gui();
			for (auto layer : _layers_stack)
				layer->on_gui();
			for (auto editor : _editors)
				editor->on_gui();
			_gui_layer->end();

			_window->on_update();
		}
	}

	void application::close()
	{
		_is_runing = false;
	}
}