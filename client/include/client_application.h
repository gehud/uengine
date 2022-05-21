#pragma once

#include <uengine/application.h>
#include <uengine/events.h>
#include <uengine/log.h>

class client_application : public ue::application
{
public:
	UE_DECLARE_EVENT(my_event, client_application)
	my_event e;
	client_application() 
	{
		e += new ue::lambda<void>([]() 
			{
				UE_INFO("On event");
			});
		e();
	}
};