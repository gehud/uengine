#include "uengine/core/application.h"

int main(void) 
{
	ue::application* app = new ue::application();
	app->run();
	delete app;
}