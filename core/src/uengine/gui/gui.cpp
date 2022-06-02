#include "gui.h"

#include "uengine/core/assertion.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace ue 
{
	void gui::window(const rectangle& rectangle, const iaction<>& action, const char* name)
	{
		UE_CORE_ASSERT(ImGui::GetCurrentContext()->WithinFrameScope, "Missing GUI scope.");
		ImGui::SetNextWindowPos(ImVec2(rectangle.x, rectangle.y), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(rectangle.width, rectangle.height), ImGuiCond_Once);
		ImGui::Begin(name);
		action();
		ImGui::End();
	}
}