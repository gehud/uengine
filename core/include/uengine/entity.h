#pragma once

#include "uengine/assertion.h"
#include "uengine/scene.h"

#include <entt/entt.hpp>

namespace ue 
{
	class entity 
	{
	private:
		entt::entity _id = { entt::null };
		scene* _scene = nullptr;
	public:
		entity() = default;

		entity(scene& scene) : _id(scene._registry.create()), _scene(&scene) { }

		static void destroy(const entity& entity) 
		{
			entity._scene->_registry.destroy(entity._id);
		}

		template<typename t>
		t& add_component() 
		{
			UE_CORE_ASSERT(!has_component<t>(), "Entity allready has component.");
			return _scene->_registry.emplace<t>(_id);
		}

		template<typename t>
		t& remove_component()
		{
			UE_CORE_ASSERT(has_component<t>(), "Entity does not have component.");
			return _scene->_registry.remove<t>(_id);
		}

		template<typename t>
		t& get_component() 
		{
			UE_CORE_ASSERT(has_component<t>(), "Entity does not have component.");
			return _scene->_registry.get<t>(_id);
		}

		template<typename t>
		bool has_component() 
		{
			return _scene->_registry.all_of<t>(_id);
		}
	};
}