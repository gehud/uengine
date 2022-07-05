#pragma once

#include "uengine/core/application.h"

namespace ue {
	extern ue::application* create_application();
}

#ifdef UE_ANDROID
	#include <android/log.h>
	#include <android_native_app_glue.h>

	void android_main(struct android_app* state) {
		__android_log_print(ANDROID_LOG_INFO, "Test", "Hello, World!");
		
		ANativeActivity_finish(state->activity);
	}
#else
	int main(void) {
		auto app = ue::create_application();
		app->run();
		delete app;
	}
#endif