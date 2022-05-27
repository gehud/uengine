#pragma once

#include <entt/entt.hpp>

namespace ue 
{
	class system 
	{
		friend class application;
	private:
		entt::registry* _registry = nullptr;
	public:
		system() = default; 
	protected:
		const entt::registry& get_registry() const { return *_registry; }
		
		virtual void on_start() { }
		virtual void on_update() { }
	};
}