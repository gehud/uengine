#include "uengine/core/scene_manager.h"

#include "uengine/core/assertion.h"

namespace ue
{
	std::map<int, scene*> scene_manager::_scenes;
	scene* scene_manager::_active_scene = nullptr;

	scene_manager::scene_manager() = default;

	void scene_manager::add_scene(scene& scene) 
	{
		int free_index = 0;
		if (_scenes.size() != 0)
		{
			for (const auto& kv : _scenes)
			{
				if (kv.first == free_index)
					free_index += 1;
			}
		}
		scene.set_index(free_index);
		_scenes.emplace(free_index, &scene);
	}

	void scene_manager::remove_scene(int index)
	{
		for (const auto& kv : _scenes)
		{
			if (kv.first == index) 
			{
				if (kv.second == _active_scene)
					_active_scene = nullptr;
				_scenes.erase(index);
				return;
			}
		}
		UE_CORE_ASSERT(false, "Failed to find the scene.");
	}

	void scene_manager::on_update()
	{
		for (const auto& kv : _scenes)
			kv.second->on_update();
	}

	void scene_manager::set_active_scene(scene& scene) 
	{
		_active_scene = &scene;
	}
}