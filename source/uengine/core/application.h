#pragma once

#include "uengine/core/window.h"

namespace ue {
	enum class application_platform {
		windows,
	};

	class application {
	public:
		application();

		virtual ~application();

		static application& get_instance() { return *_instance; }

		application_platform get_platfrom() const { return _platform; }
		bool is_runing() { return _runing; }

		void run();
		void stop();

		virtual void update();
	private:
		window* _window;
		static application* _instance;
		static application_platform	_platform;
		bool _runing = false;
	};
}