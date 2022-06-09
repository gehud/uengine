#include "gui.h"

#include "uengine/core/assertion.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace ue 
{
	void gui::window(const rectangle& rectangle, const ifunction<void>& function, const char* name)
	{
		UE_CORE_ASSERT(ImGui::GetCurrentContext()->WithinFrameScope, "Missing GUI scope.");
		ImGui::SetNextWindowPos(ImVec2(rectangle.x, rectangle.y), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(rectangle.width, rectangle.height), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowCollapsed(false, ImGuiCond_FirstUseEver);
		ImGui::Begin(name, nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		function();
		ImGui::End();
	}
}