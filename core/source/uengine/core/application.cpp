#include "uengine/core/application.h"

namespace ue {
	application* application::_instance = nullptr;

	application::application() {
		_instance = this;
	}

	application::~application() {

	}

	void application::run() {
		_runing = true;

		while (_runing) {

		}
	}

	void application::close() {
		_runing = false;
	}
}