#pragma once

#include "uengine/window.h"

namespace ue 
{
	class application 
	{
	private:
		bool _is_runing;
		window* _window;
	public:
		application();

		~application();

		void run();

		void close();
	};
}