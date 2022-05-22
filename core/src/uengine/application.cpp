#include "uengine/application.h"

#include "uengine/log.h"
#include "uengine/rendering/gl.h"

namespace ue 
{
	application::application() : _is_runing(true)
	{
		log::init();
		_window = window::create(window_properties("UEngine", 1280, 720));
		_window->on_close += new lambda<void>([this]() { close(); });
		gl::init();
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
			on_update();
			_window->on_update();
		}
	}

	void application::close()
	{
		_is_runing = false;
	}
}