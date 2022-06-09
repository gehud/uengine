#pragma once

#include "uengine/core/events.h"
#include "uengine/core/application.h"
#include "uengine/core/windows/windows_window.h"
#include "uengine/math/vector2.h"

namespace ue 
{
	class input
	{
		friend class application;
		friend class windows_window;
	public:
		UE_DECLARE_EVENT(key_pressed_event, input, int, int)
		static key_pressed_event on_key_pressed;

		UE_DECLARE_EVENT(key_released_event, input, int)
		static key_released_event on_key_released;

		UE_DECLARE_EVENT(mouse_botton_event, input, int)
		static mouse_botton_event on_mouse_button_pressed;
		static mouse_botton_event on_mouse_button_released;

		UE_DECLARE_EVENT(mouse_moved_event, input, float, float)
		static mouse_moved_event on_mouse_moved;

		UE_DECLARE_EVENT(mouse_scrolled_event, input, float, float)
		static mouse_scrolled_event on_mouse_scrolled;
	protected:
		static vector2 last_mouse_position;
		static vector2 mouse_position;
		static vector2 mouse_position_delta;
	private:
		static input* _instance;
	public:
		static bool get_key_down(int keycode)
		{
			return _instance->get_key_down_impl(keycode);
		}

		static bool get_key(int keycode)
		{
			return _instance->get_key_impl(keycode);
		}

		static bool get_key_up(int keycode)
		{
			return _instance->get_key_up_impl(keycode);
		}

		static bool get_mouse_button_down(int button)
		{
			return _instance->get_mouse_button_down_impl(button);
		}

		static bool get_mouse_button(int button)
		{
			return _instance->get_mouse_button_impl(button);
		}

		static bool get_mouse_button_up(int button)
		{
			return _instance->get_mouse_button_up_impl(button);
		}

		static vector2 get_mouse_position()
		{
			return _instance->get_mouse_position_impl();
		}

		static vector2 get_mouse_position_delta() { return mouse_position_delta; }
	protected:
		virtual bool get_key_down_impl(int keycode) = 0;
		virtual bool get_key_impl(int keycode) = 0;
		virtual bool get_key_up_impl(int keycode) = 0;

		virtual bool get_mouse_button_down_impl(int button) = 0;
		virtual bool get_mouse_button_impl(int button) = 0;
		virtual bool get_mouse_button_up_impl(int button) = 0;

		virtual vector2 get_mouse_position_impl() = 0;
	private:
		static void invoke_key_pressed_event(int key, int repeat_count)
		{
			on_key_pressed.invoke(key, repeat_count);
		}

		static void invoke_key_released_event(int key)
		{
			on_key_released.invoke(key);
		}

		static void invoke_mouse_button_pressed_event(int button)
		{
			on_mouse_button_pressed.invoke(button);
		}

		static void invoke_mouse_button_released_event(int button)
		{
			on_mouse_button_released.invoke(button);
		}

		static void invoke_mouse_moved_event(float x, float y)
		{
			on_mouse_moved.invoke(x, y);
		}

		static void invoke_mouse_scrolled_event(float offset_x, float offset_y)
		{
			on_mouse_scrolled.invoke(offset_x, offset_y);
		}
	};
}