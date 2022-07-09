#pragma once

#include "types.h"
#include "event.h"

#include <glfw/glfw3.h>

namespace ue {
	class window {
	public:
		UE_DECLARE_EVENT(close_event, window)
		close_event on_close;
		UE_DECLARE_EVENT(resize_event, window, uint32, uint32)
		resize_event on_resize;

		window(uint32 width, uint32 height, const char* title);
		~window();

		static window& get_instance() { return *_instance; }

		uint32 get_width() const { return _width; }
		uint32 get_height() const { return _height; }

		bool is_vsync() const { return _vsync; }
		void set_vsync(bool value);

		void update() const;

		void* get_handle() const { return _handle; }
	protected:
		void invoke_close_event() {
			on_close();
		}
		void invoke_resize_event(uint32 width, uint32 height) {
			on_resize(width, height);
		}
	private:
		static window* _instance;
		uint32 _width, _height;
		const char* _title;
		bool _vsync = false;
		GLFWwindow* _handle;
	};
}