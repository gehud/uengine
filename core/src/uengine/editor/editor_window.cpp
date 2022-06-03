#include "editor_window.h"

#include "uengine/core/assertion.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace ue 
{
	editor_window::editor_window(const char* name) : name(name) { }

	void editor_window::show()
	{
		UE_CORE_ASSERT(ImGui::GetCurrentContext()->WithinFrameScope, "Missing GUI scope.");
		ImGui::SetNextWindowPos(ImVec2(rectangle.x, rectangle.y), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(rectangle.width, rectangle.height), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowCollapsed(false, ImGuiCond_FirstUseEver);
		ImGui::Begin(name, nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		on_gui();
		ImVec2 pos = ImGui::GetWindowPos();
		rectangle.x = pos.x;
		rectangle.y = pos.y;
		ImVec2 size = ImGui::GetWindowSize();
		rectangle.width = size.x;
		rectangle.height = size.y;
		ImGui::End();
	}
}