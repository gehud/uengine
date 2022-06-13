#pragma once

namespace ue 
{
	class application 
	{
	private:
		static application* _instance;

		bool _runing = false;
	public:
		application();

		~application();

		static application& get_instance() { return *_instance; }

		void run();

		void close();
	};
}