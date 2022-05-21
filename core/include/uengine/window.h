#pragma once

#include "uengine/events.h"

namespace ue 
{
	struct window_properties 
	{
		const char* title;
		unsigned int width, height;

		window_properties(const char* title, unsigned int width, unsigned int height)
			: title(title), width(width), height(height) { }
	};

	class window 
	{
	public:
		UE_DECLARE_EVENT(resize_event, window, unsigned int, unsigned int)
		resize_event on_resize;
		UE_DECLARE_EVENT(close_event, window)
		close_event on_close;
	public:
		static window* create(const window_properties& properties);

		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;

		virtual bool is_vsync() const = 0;
		virtual void set_vsync(bool value) = 0;

		virtual void on_update() const = 0;

		virtual void* get_native_ptr() const = 0;
	protected:
		void invoke_resize_event(unsigned int width, unsigned int height)
		{
			on_resize.invoke(width, height);
		}

		void invoke_close_event()
		{
			on_close.invoke();
		}
	};
}