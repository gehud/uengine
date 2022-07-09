#pragma once

#include "application.h"

namespace ue {
	extern ue::application* create_application();
}

int main(void) {
	auto app = ue::create_application();
	app->run();
	delete app;
}