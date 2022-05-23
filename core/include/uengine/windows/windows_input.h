#pragma once

#include "uengine/input.h"

namespace ue 
{
	class windows_input final : public input 
	{
	private:
		bool is_key_pressed_impl(int keycode) override;

		bool is_mouse_button_pressed_impl(int button) override;

		glm::vec2 get_mouse_position_impl() override;
	};
}