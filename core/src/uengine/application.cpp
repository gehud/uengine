#include "uengine/application.h"

#include "uengine/log.h"

#include <glad/glad.h>

namespace ue 
{
	application::application() : _is_runing(true)
	{
		log::init();
		_window = window::create(window_properties("UEngine", 1280, 720));
		_window->on_close += new lambda<void>([this]() { close(); });
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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->on_update();
		}
	}

	void application::close()
	{
		_is_runing = false;
	}
}