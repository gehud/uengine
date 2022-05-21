#include "uengine/application.h"

#include "uengine/log.h"

namespace ue 
{
	application::application() : _is_runing(true)
	{
		log::init();
		UE_CORE_INFO("Welcome to the UEngine!");
	}

	void application::run()
	{
		while (_is_runing)
		{

		}
	}

	void application::close()
	{
		_is_runing = false;
	}
}