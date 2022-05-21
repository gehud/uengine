#include "uengine/application.h"

#include "uengine/log.h"

namespace ue 
{
	application::application() : _is_runing(true)
	{
		log::init();
		_window = window::create(window_properties("UEngine", 1280, 720));
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
			_window->on_update();
		}
	}

	void application::close()
	{
		_is_runing = false;
	}
}