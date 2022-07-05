#include "application.h"

#include "log.h"

namespace ue {
	application* application::_instance = nullptr;

#if defined(UE_WINDOWS)
	application_platform application::_platform = application_platform::windows;
#elif defined(UE_ANDROID)
	application_platform application::_platform = application_platform::android;
#endif

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

	void application::close() {
		_runing = false;
	}
}