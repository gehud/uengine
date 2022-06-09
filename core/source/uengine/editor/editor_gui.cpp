#include "editor_gui.h"

#include "uengine/core/assertion.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace ue 
{
	rectangle editor_gui::window(const rectangle& rectangle, const ifunction<void>& function, const char* name)
	{
		UE_CORE_ASSERT(ImGui::GetCurrentContext()->WithinFrameScope, "Missing GUI scope.");
		ImGui::SetNextWindowPos(ImVec2(rectangle.x, rectangle.y), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(rectangle.width, rectangle.height), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowCollapsed(false, ImGuiCond_FirstUseEver);
		ImGui::Begin(name, nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		function();
		ImVec2 window_pos = ImGui::GetWindowPos();
		ImVec2 window_size = ImGui::GetWindowSize();
		ue::rectangle rect(window_pos.x, window_pos.y, window_size.x, window_size.y);
		ImGui::End();
		return rect;
	}
}