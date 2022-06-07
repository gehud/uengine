#include "application.h"

#include "uengine/core/assertion.h"
#include "uengine/core/log.h"
#include "uengine/core/input.h"
#include "uengine/core/time.h"
#include "uengine/core/scene_manager.h"
#include "uengine/core/system_manager.h"
#include "uengine/rendering/gl.h"

namespace ue 
{
	application* application::_instance = nullptr;

	application_platform application::_platform = application_platform::windows;

	application::application()
	{
		UE_CORE_ASSERT(_instance == nullptr, "Application allready exists.");
		_instance = this;

		time::init();
		log::init();
		_window = window::create({ "UEngine", 1280, 720 });
		_window->on_close += new lambda<void>([this](){ close(); });

		gl::init();

		_gui_layer = new gui_layer();
		push_overlay(_gui_layer);

		UE_CORE_INFO("Welcome to the UEngine!");
	}

	application::~application()
	{
		for (auto editor : _editors)
			delete editor;
		gl::terminate();
		delete _window;
	}

	void application::run()
	{
		_runing = true;

		system_manager::on_start();

		while (_runing)
		{
			time::update();

			input::mouse_position = input::get_mouse_position();
			input::mouse_position_delta = input::mouse_position - input::last_mouse_position;
			input::last_mouse_position = input::mouse_position;

			system_manager::on_update();

			on_update();

			for (auto layer : _layers_stack)
				layer->on_update();

			scene_manager::on_update();

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
		_runing = false;
	}
}