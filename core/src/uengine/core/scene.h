#pragma once

#include <entt/entt.hpp>

namespace ue
{
	class scene
	{
		friend class application;
		friend class entity;
	private:
		entt::registry _registry;
	public:
		scene() = default;
	private:
		void on_update();
	};
}