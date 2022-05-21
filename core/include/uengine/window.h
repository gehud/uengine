#pragma once

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
		static window* create(const window_properties& properties);

		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;

		virtual bool is_v_sync() const = 0;
		virtual void set_v_sync(bool value) = 0;

		virtual void on_update() const = 0;

		virtual void* get_native_ptr() const = 0;
	};
}