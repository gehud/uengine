#pragma once

#include <glfw/glfw3.h>

namespace ue {
	class time final {
		friend class application;
	public:
		time() = delete;

		static float get_time() { return _time; }
		static float get_delta() { return _delta; }
	private:
		static float _last_frame_time;
		static float _time;
		static float _delta;
	private:
		static void update()
		{
			_time = static_cast<float>(glfwGetTime());
			_delta = _time - _last_frame_time;
			_last_frame_time = _time;
		}
	};
}