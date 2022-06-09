#pragma once

#include "uengine/core/window.h"

struct GLFWwindow;

namespace ue 
{
	class windows_window : public window 
	{
	private:
		const char* _title;
		unsigned int _width, _height;
		GLFWwindow* _window;
		bool _is_vsync = false;
	public:
		windows_window(const window_properties& properties);

		~windows_window();

		unsigned int get_width() const override { return _width; }

		unsigned int get_height() const override { return _height; }

		bool is_vsync() const override { return _is_vsync; }

		void set_vsync(bool value) override;

		void on_update() const override;

		void* get_native_window() const override { return static_cast<void*>(_window); }
	};
}