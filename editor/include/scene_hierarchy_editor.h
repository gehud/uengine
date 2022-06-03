#pragma once

#include <uengine/gui.h>
#include <uengine/editor.h>

class scene_hierarchy_editor : public ue::editor 
{
protected:
	void on_gui() override 
	{
		ue::gui::window({ 50, 50, 100, 500 }, ue::lambda<>([]() {}), "Hierarchy");
	}
};