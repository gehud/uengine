#pragma once

namespace ue {
	class application {
	private:
		static application* _instance;

		bool _runing = false;
	public:
		application();

		virtual ~application();

		static application& get() { return *_instance; }

		void run();

		void close();
	};
}