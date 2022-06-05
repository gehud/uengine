//#pragma once
//
//#include "uengine/core/script_system.h"
//#include "uengine/core/scene_manager.h"
//
//#include <vector>
//
//namespace ue 
//{
//	class script_manager final
//	{
//		friend class application;
//	private:
//		static std::vector<script_system<script>*> _systems;
//	public:
//		template<typename t, typename std::enable_if<std::is_base_of<script, t>::value, bool>::type = true>
//		static void add_system() 
//		{
//			script_system<t>* s = new script_system<t>();
//			if (scene_manager::_active_scene != nullptr)
//				static_cast<system>s->_entities = &scene_manager::_active_scene->_entities;
//			_systems.push_back(s);
//		}
//	private:
//		static void on_start() 
//		{
//			for (auto& system : _systems)
//				system->on_start();
//		}
//
//		static void on_update() 
//		{
//			for (auto& system : _systems)
//				system->on_update();
//		}
//	};
//}