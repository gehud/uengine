#pragma once

#include "event.h"
#include "uengine/math/vector2.h"

namespace ue {
	class input final {
		friend class window;
		friend class application;
	public:
		UE_DECLARE_EVENT(key_pressed_event, input, int, int);
		static key_pressed_event on_key_pressed;

		UE_DECLARE_EVENT(key_released_event, input, int);
		static key_released_event on_key_released;

		UE_DECLARE_EVENT(mouse_botton_event, input, int);
		static mouse_botton_event on_mouse_button_pressed;
		static mouse_botton_event on_mouse_button_released;

		UE_DECLARE_EVENT(mouse_moved_event, input, float, float);
		static mouse_moved_event on_mouse_moved;

		UE_DECLARE_EVENT(mouse_scrolled_event, input, float, float);
		static mouse_scrolled_event on_mouse_scrolled;

		static bool get_key_down(int key);

		static bool get_key(int key);

		static bool get_key_up(int key);

		static bool get_mouse_button_down(int button);

		static bool get_mouse_button(int button);

		static bool get_mouse_button_up(int button);

		static vector2 get_mouse_position() { return mouse_position; }

		static vector2 get_mouse_position_delta() { return mouse_position_delta; }
	protected:
		static vector2 last_mouse_position;
		static vector2 mouse_position;
		static vector2 mouse_position_delta;

		static void update();

		static void invoke_key_pressed_event(int key, int repeat_count)
		{
			on_key_pressed(key, repeat_count);
		}

		static void invoke_key_released_event(int key)
		{
			on_key_released(key);
		}

		static void invoke_mouse_button_pressed_event(int button)
		{
			on_mouse_button_pressed(button);
		}

		static void invoke_mouse_button_released_event(int button)
		{
			on_mouse_button_released(button);
		}

		static void invoke_mouse_moved_event(float position_x, float position_y)
		{
			on_mouse_moved(position_x, position_y);
		}

		static void invoke_mouse_scrolled_event(float offset_x, float offset_y)
		{
			on_mouse_scrolled(offset_x, offset_y);
		}
	};
}