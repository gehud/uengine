#include "time.h"

#include "uengine/core/application.h"
#include "uengine/core/windows/windows_time.h"

namespace ue 
{
	std::unique_ptr<time> time::_instance = nullptr;

	double time::_last_frame_time = 0.0;
	double time::_time = 0.0;
	double time::_delta = 0.0;

	static bool _initialized = false;

	void time::init()
	{
		if (_initialized)
			return;

		switch (application::get_platform()) 
		{
		case application_platform::windows:
			_instance = std::unique_ptr<time>(new windows_time());
		}

		_initialized = true;
	}
}