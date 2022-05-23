#pragma once

#include "uengine/events.h"
#include "uengine/application.h"
#include "uengine/windows/windows_window.h"

#include <glm/vec2.hpp>

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
		static glm::vec2 last_mouse_position;
		static glm::vec2 mouse_delta;
	private:
		static input* _instance;
	public:
		static bool is_key_pressed(int keycode)
		{
			return _instance->is_key_pressed_impl(keycode);
		}

		static bool is_mouse_button_pressed(int button)
		{
			return _instance->is_mouse_button_pressed_impl(button);
		}

		static glm::vec2 get_mouse_position() 
		{
			return _instance->get_mouse_position_impl();
		}

		static glm::vec2 get_mouse_delta() 
		{
			return _instance->get_mouse_delta_impl();
		}
	protected:
		virtual bool is_key_pressed_impl(int keycode) = 0;

		virtual bool is_mouse_button_pressed_impl(int button) = 0;

		virtual glm::vec2 get_mouse_position_impl() = 0;

		virtual glm::vec2 get_mouse_delta_impl() = 0;
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