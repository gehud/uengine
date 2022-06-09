#include "entity.h"

namespace ue
{
	entity::entity(scene* scene) : _id(scene->_entities.create()), _scene(scene)
	{
		add_component<transform>();
	}
}