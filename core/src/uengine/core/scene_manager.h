#pragma once

#include "uengine/core/scene.h"

#include <map>

namespace ue 
{
	class scene_manager final
	{
		friend class application;
		friend class entity_manager;
		friend class system_manager;
	private:
		static std::map<int, scene*> _scenes;
		static scene* _active_scene;
	public:
		static int get_scene_count() { return static_cast<int>(_scenes.size()); }

		static void add_scene(scene& scene);

		static void remove_scene(int index);

		static void set_active_scene(scene& scene);
	private:
		scene_manager();

		static void on_update();
	};
}