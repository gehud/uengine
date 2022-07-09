#pragma once

#include "types.h"

#include <glfw/glfw3.h>

namespace ue {
	class window {
	public:
		window(uint32 width, uint32 height, const char* title);
		~window();

		static window& get_instance() { return *_instance; }

		uint32 get_width() const { return _width; }
		uint32 get_height() const { return _height; }

		bool is_vsync() const { return _vsync; }
		void set_vsync(bool value);

		void update() const;

		void* get_handle() const { return _handle; }
	private:
		static window* _instance;
		uint32 _width, _height;
		const char* _title;
		bool _vsync = false;
		GLFWwindow* _handle;
	};
}