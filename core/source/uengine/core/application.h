#pragma once

namespace ue {
	enum class application_platform {
		windows,
		android
	};

	class application {
	private:
		static application* _instance;
		static application_platform	_platform;

		bool _runing = false;
	public:
		application();

		virtual ~application();

		static application& get() { return *_instance; }

		void run();

		void stop();
	};
}