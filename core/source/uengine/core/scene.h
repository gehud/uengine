#pragma once

#include <entt/entt.hpp>

namespace ue
{
	class scene
	{
		friend class scene_manager;
		friend class entity_manager;
		friend class system_manager;
		friend class entity;
	private:
		int _index = 0;
		const char* _name = "Untitled";
		entt::registry _entities;
	public:
		scene() = default;

		const char* get_name() const { return _name; }

		int get_index() const { return _index; }
	private:
		void set_name(const char* value) { _name = value; }

		void set_index(int value) { _index = value; }

		void on_update();
	};
}