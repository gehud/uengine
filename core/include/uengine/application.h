#pragma once

namespace ue 
{
	class application 
	{
	private:
		bool _is_runing;
	public:
		application();

		void run();

		void close();
	};
}