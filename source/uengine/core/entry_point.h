#pragma once

#include "uengine/core/application.h"

namespace ue {
	extern ue::application* create_application();
}

int main(void) {
	auto application = ue::create_application();
	application->run();
	delete application;
}