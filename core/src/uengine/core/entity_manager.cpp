#include "entity_manager.h"

#include "uengine/core/assertion.h"

namespace ue 
{
    entity_manager::entity_manager() = default;

    entity& entity_manager::create()
    {
        UE_CORE_ASSERT(scene_manager::_active_scene != nullptr, "Missing active scene.");
        return entity(*scene_manager::_active_scene);
    }

    void entity_manager::destroy(const entity& entity)
    {
        entity._scene->_entities.destroy(entity._id);
    }
}