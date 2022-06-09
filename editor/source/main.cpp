#include "editor_application.h"

int main(void) 
{
	editor_application* app = new editor_application();
	app->run();
	delete app;
}