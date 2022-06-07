#pragma once

#include "uengine/core/memory.h"
#include "uengine/core/entity.h"
#include "uengine/core/scene_manager.h"

namespace ue 
{
	class entity_manager final
	{
	public:
		static reference<entity> create();

		static void destroy(reference<entity>& entity);
	private:
		entity_manager();
	};
}