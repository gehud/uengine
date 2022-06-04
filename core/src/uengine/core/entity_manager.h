#pragma once

#include "uengine/core/entity.h"
#include "uengine/core/scene_manager.h"

namespace ue 
{
	class entity_manager final
	{
	public:
		static entity& create();

		static void destroy(const entity& entity);
	private:
		entity_manager();
	};
}