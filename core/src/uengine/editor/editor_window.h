#pragma once

#include "uengine/core/rectangle.h"

namespace ue 
{
	class editor_window
	{
	protected:
		const char* name;
		rectangle rectangle = { 64, 64, 640, 480 };
	public:
		editor_window(const char* name);

		void show();

		ue::rectangle get_rectangle() const { return rectangle; }
	protected:
		virtual void on_gui() { }
	};
}