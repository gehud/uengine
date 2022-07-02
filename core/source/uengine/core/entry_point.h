#pragma once

#include "uengine/core/application.h"
#include "uengine/core/configuration.h"

#include <iostream>

namespace ue {
	extern ue::application* create_application();
}

#ifdef UE_ANDROID
	#include <android_native_app_glue.h>

	void android_main(struct android_app* app) {
		while (true) {
		}
	}
#else
	int main(void) {
		auto app = ue::create_application();
		app->run();
		delete app;
	}
#endif