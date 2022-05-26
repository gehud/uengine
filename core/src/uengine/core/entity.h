#pragma once

#include "uengine/core/assertion.h"
#include "uengine/core/component.h"
#include "uengine/core/transform.h"
#include "uengine/core/scene.h"

#include <entt/entt.hpp>

namespace ue 
{
	class entity 
	{
	private:
		entt::entity _id = { entt::null };
		scene* _scene = nullptr;
	public:
		entity();
		entity(const entt::entity& entity);
		entity(scene& scene);

		static void destroy(const entity& entity);

		template<typename t, typename std::enable_if<std::is_base_of<component, t>::value, bool>::type = true>
		t& add_component() 
		{
			UE_CORE_ASSERT(!has_component<t>(), "Entity allready has component.");
			return _scene->_registry.emplace<t>(_id, *this);
		}

		template<typename t, typename std::enable_if<std::is_base_of<component, t>::value 
			&& !std::is_same<t, transform>::value, bool>::type = true>
		void remove_component()
		{
			UE_CORE_ASSERT(has_component<t>(), "Entity does not have component.");
			_scene->_registry.remove<t>(_id);
		}

		template<typename t, typename std::enable_if<std::is_base_of<component, t>::value, bool>::type = true>
		t& get_component() 
		{
			UE_CORE_ASSERT(has_component<t>(), "Entity does not have component.");
			return _scene->_registry.get<t>(_id);
		}

		template<typename t, typename std::enable_if<std::is_base_of<component, t>::value, bool>::type = true>
		bool has_component() 
		{
			return _scene->_registry.all_of<t>(_id);
		}
	};
}