#include "uengine/core/application.h"

#include "uengine/core/time.h"
#include "uengine/core/input.h"
#include "uengine/core/assertion.h"
#include "uengine/rendering/graphics.h"

#include <glad/glad.h>

namespace ue {
	application* application::_instance = nullptr;

	application_platform application::_platform = application_platform::windows;

	application::application() {
		UE_CORE_ASSERT(_instance == nullptr, "Application allready exists.");
		_instance = this;
		ue::log::initialize();
		_window = new ue::window(1280, 720, "UEngine");
		_window->on_close += new ue::lambda<void>([this]() { stop(); });
		ue::graphics::initialize();
	}

	application::~application() {
		delete _window;
		ue::graphics::terminate();
		_instance = nullptr;
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

	void application::update() {
	}
}