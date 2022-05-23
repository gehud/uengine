#pragma once

#include "uengine/application.h"

namespace ue 
{
	class time final 
	{
		friend class application;
	private:
		static double _last_frame_time;
		static double _time;
		static double _delta;
	public:
		static float get_time() { return static_cast<float>(_time); }
		static float get_delta() { return static_cast<float>(_delta); }
	};
}