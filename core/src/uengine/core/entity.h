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
		friend class entity_manager;
	private:
		entt::entity _id = entt::null;
		scene* _scene = nullptr;
	public:
		template<typename t, typename std::enable_if<std::is_base_of<component, t>::value 
			&& std::is_constructible<t, const entity&>::value, bool>::type = true>
		t& add_component() const
		{
			UE_CORE_ASSERT(!has_component<t>(), "Entity allready has component.");
			return _scene->_entities.emplace<t>(_id, *this);
		}

		template<typename t, typename std::enable_if<std::is_base_of<component, t>::value 
			&& !std::is_same<t, transform>::value, bool>::type = true>
		void remove_component() const
		{
			UE_CORE_ASSERT(has_component<t>(), "Entity does not have component.");
			_scene->_entities.remove<t>(_id);
		}

		template<typename t, typename std::enable_if<std::is_base_of<component, t>::value, bool>::type = true>
		t& get_component() const
		{
			UE_CORE_ASSERT(has_component<t>(), "Entity does not have component.");
			return _scene->_entities.get<t>(_id);
		}

		template<typename t, typename std::enable_if<std::is_base_of<component, t>::value, bool>::type = true>
		bool has_component() const
		{
			return _scene->_entities.all_of<t>(_id);
		}
	private:
		entity(const entt::entity& entity);
		entity(scene& scene);
	};
}