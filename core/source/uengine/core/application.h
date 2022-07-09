#pragma once

#include "window.h"

namespace ue {
	enum class application_platform {
		windows,
		android
	};

	class application {
	public:
		application();
		virtual ~application();

		static application& get_instance() { return *_instance; }

		void run();
		void stop();

		virtual void update() {}
	private:
		static application* _instance;
		static application_platform	_platform;
		window* _window;
		bool _runing = false;
	};
}