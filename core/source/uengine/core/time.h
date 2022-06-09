#pragma once

#include <memory>

namespace ue 
{
	class time
	{
		friend class application;
	private:
		static std::unique_ptr<time> _instance;

		static double _last_frame_time;
		static double _time;
		static double _delta;
	public:
		static void init();

		static float get_time() { return static_cast<float>(_time); }
		static float get_delta() { return static_cast<float>(_delta); }
	protected:
		virtual double get_time_impl() const = 0;
	private:
		static void update() 
		{
			_time = _instance->get_time_impl();
			_delta = _time - _last_frame_time;
			_last_frame_time = _time;
		}
	};
}