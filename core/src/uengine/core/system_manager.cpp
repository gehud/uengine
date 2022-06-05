#include "system_manager.h"

namespace ue 
{
	std::set<system*> system_manager::_systems;

	void system_manager::on_start()
	{
		for (auto& system : _systems)
			system->on_start();
	}

	void system_manager::on_update()
	{
		for (auto& system : _systems)
			system->on_update();
	}
}