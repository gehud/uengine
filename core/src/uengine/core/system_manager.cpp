#include "system_manager.h"

namespace ue 
{
	std::unordered_map<size_t, system*> system_manager::_systems;

	void system_manager::on_start()
	{
		for (auto& kv : _systems)
			kv.second->on_start();
	}

	void system_manager::on_update()
	{
		for (auto& kv : _systems)
			kv.second->on_update();
	}
}