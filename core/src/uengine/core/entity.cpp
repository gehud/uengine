#include "entity.h"

namespace ue
{
	entity::entity() = default;

	entity::entity(const entt::entity & entity) : _id(entity) { }

	entity::entity(scene& scene) : _id(scene._registry.create()), _scene(&scene)
	{
		add_component<transform>();
	}

	void entity::destroy(const entity& entity)
	{
		entity._scene->_registry.destroy(entity._id);
	}
}