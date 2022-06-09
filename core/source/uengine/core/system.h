#pragma once

#include <entt/entt.hpp>

namespace ue 
{
	class system 
	{
		friend class system_manager;
	private:
		entt::registry* _entities = nullptr;
	public:
		system() = default; 
	protected:
		entt::registry& get_registry() { return *_entities; }
		
		virtual void on_start() { }
		virtual void on_update() { }
	};
}