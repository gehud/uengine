#include "application.h"

#include "time.h"
#include "input.h"
#include "assertion.h"
#include "uengine/rendering/graphics.h"

#include <glad/glad.h>

namespace ue {
	application* application::_instance = nullptr;

	application_platform application::_platform = application_platform::windows;

	application::application() {
		UE_CORE_ASSERT(_instance == nullptr, "Application allready exists.");
		_instance = this;

		log::initialize();

		_window = new window(1280, 720, "UEngine");
		_window->on_close += new lambda<void>([this]() {
			stop();
		});

		graphics::initialize();

		UE_CORE_LOG_INFO("Welcome to the UEngine!");
	}

	application::~application() {
		delete _window;
		graphics::terminate();
	}

	void application::run() {
		_runing = true;

		while (_runing) {
			time::update();
			input::update();

			update();

			_window->update();
		}
	}

	void application::stop() {
		_runing = false;
	}
}