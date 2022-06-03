#pragma once

#include <uengine/gui.h>
#include <uengine/editor.h>

class scene_hierarchy_window : public ue::editor_window
{
public:
	scene_hierarchy_window() : editor_window("Hierarchy") { }
protected:
	void on_gui() override 
	{
	}
};