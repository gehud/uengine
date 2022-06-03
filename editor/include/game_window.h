#pragma once

#include <uengine.h>

#include <imgui.h>

class game_window : public ue::editor_window
{
private:
	std::shared_ptr<ue::framebuffer>& _framebuffer;
public:
	game_window(std::shared_ptr<ue::framebuffer>& framebuffer) 
		: _framebuffer(framebuffer), editor_window("Game") { }
protected:
	void on_gui() override 
	{
		ImGui::Image(reinterpret_cast<void*>(_framebuffer->get_color_buffer_id()),
			ImVec2(rectangle.width, rectangle.height), ImVec2(0, 1), ImVec2(1, 0));
	}
};