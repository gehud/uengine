#include "input.h"

#include "uengine/core/windows/windows_input.h"

namespace ue 
{
	input* input::_instance = new windows_input();

	vector2 input::last_mouse_position = vector2::zero;
	vector2 input::mouse_position = vector2::zero;
	vector2 input::mouse_position_delta = vector2::zero;

	input::key_pressed_event input::on_key_pressed;
	input::key_released_event input::on_key_released;
	input::mouse_botton_event input::on_mouse_button_pressed;
	input::mouse_botton_event input::on_mouse_button_released;
	input::mouse_moved_event input::on_mouse_moved;
	input::mouse_scrolled_event input::on_mouse_scrolled;
}