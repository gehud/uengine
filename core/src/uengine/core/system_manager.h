#pragma once

#include "uengine/core/system.h"
#include "uengine/core/assertion.h"
#include "uengine/core/scene_manager.h"

#include <vector>

namespace ue 
{
	class system_manager final
	{
		friend class application;
	private:
		static std::vector<system*> _systems;
	public:
		template<typename t, typename std::enable_if<std::is_base_of<system, t>::value, bool>::type = true>
		static void add_system()
		{
			t* s = new t();
			if (scene_manager::_active_scene != nullptr) 
				s->_entities = &scene_manager::_active_scene->_entities;
			_systems.push_back(s);
		}
	private:
		system_manager();

		static void on_start();
		static void on_update();
	};
}