#include "input.h"

#include "uengine/core/windows/windows_input.h"

namespace ue 
{
	input* input::_instance = new windows_input();

	glm::vec2 input::last_mouse_position = glm::vec2(0.0f);
	glm::vec2 input::mouse_delta = glm::vec2(0.0f);

	input::key_pressed_event input::on_key_pressed;
	input::key_released_event input::on_key_released;
	input::mouse_botton_event input::on_mouse_button_pressed;
	input::mouse_botton_event input::on_mouse_button_released;
	input::mouse_moved_event input::on_mouse_moved;
	input::mouse_scrolled_event input::on_mouse_scrolled;
}