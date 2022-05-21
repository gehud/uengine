#pragma once

#include "uengine/window.h"

struct GLFWwindow;

namespace ue 
{
	class windows_window : public window 
	{
	private:
		const char* _title;
		unsigned int _width, _height;
		GLFWwindow* _window;
		bool _is_v_sync = false;
	public:
		windows_window(const window_properties& properties);

		~windows_window();

		unsigned int get_width() const override { return _width; }

		unsigned int get_height() const override { return _height; }

		bool is_v_sync() const override { return _is_v_sync; }

		void set_v_sync(bool value) override;

		void on_update() const override;

		void* get_native_ptr() const override { return static_cast<void*>(_window); }
	};
}