#pragma once

namespace ue 
{
	class layer 
	{
	public:
		virtual void on_attach() { }
		virtual void on_detach() { }

		virtual void on_update() { }

		virtual void on_gui() { }
	};
}