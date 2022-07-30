#pragma once

#include "uengine/core/event.h"
#include "uengine/math/vector2.h"

#include <glfw/glfw3.h>

namespace ue {
	class window {
	public:
		UE_DECLARE_EVENT(close_event, window);
		close_event on_close;
		UE_DECLARE_EVENT(resize_event, window, int, int);
		resize_event on_resize;
	public:
		window(int width, int height, const char* title);

		~window();

		static reference<window> create(int width, int height, const char* title);

		static window& get_instance() { return *_instance; }

		int get_width() const { return _width; }
		int get_height() const { return _height; }

		vector2f get_position() const {
			int x, y;
			glfwGetWindowPos(_handle, &x, &y);
			return vector2f(x, y);
		}

		bool is_vsync() const { return _vsync; }
		void set_vsync(bool value);

		void update() const;

		void* get_handle() const { return _handle; }
	protected:
		void invoke_close_event() {
			on_close();
		}

		void invoke_resize_event(int width, int height) {
			on_resize(width, height);
		}
	private:
		static window* _instance;
		int _width, _height;
		const char* _title;
		bool _vsync = false;
		GLFWwindow* _handle;
	};
}