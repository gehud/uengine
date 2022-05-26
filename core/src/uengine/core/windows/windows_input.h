#pragma once

#include "uengine/core/input.h"

namespace ue 
{
	class windows_input final : public input 
	{
	private:
		bool get_key_down_impl(int keycode) override;
		bool get_key_impl(int keycode) override;
		bool get_key_up_impl(int keycode) override;

		bool get_mouse_button_down_impl(int button) override;
		bool get_mouse_button_impl(int button) override;
		bool get_mouse_button_up_impl(int button) override;

		vector2 get_mouse_position_impl() override;
	};
}