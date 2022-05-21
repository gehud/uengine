#include "uengine/application.h"

namespace ue 
{
	application::application() : _is_runing(true)
	{
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