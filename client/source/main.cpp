#include "client_application.h"

int main(void) 
{
	client_application* app = new client_application();
	app->run();
	delete app;
}