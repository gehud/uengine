#pragma once

#include "uengine/core/system.h"
#include "uengine/core/assertion.h"
#include "uengine/core/scene_manager.h"

#include <typeinfo>
#include <unordered_map>

namespace ue 
{
	class system_manager final
	{
		friend class application;
	private:
		static std::unordered_map<size_t, system*> _systems;
	public:
		template<typename t, typename std::enable_if<std::is_base_of<system, t>::value, bool>::type = true>
		static void add_system()
		{
			size_t id = typeid(t).hash_code();
			if (_systems.find(id) != _systems.end())
				return;
			t* s = new t();
			if (scene_manager::_active_scene != nullptr) 
				static_cast<system*>(s)->_entities = &scene_manager::_active_scene->_entities;
			_systems.emplace(id, s);
		}
	private:
		system_manager();

		static void on_start();
		static void on_update();
	};
}