#include "application.h"

#include "log.h"

namespace ue {
	application* application::_instance = nullptr;

	application_platform application::_platform = application_platform::windows;

	application::application() {
		_instance = this;
		log::initialize();
	}

	application::~application() {

	}

	void application::run() {
		_runing = true;

		while (_runing) {

		}
	}

	void application::stop() {
		_runing = false;
	}
}