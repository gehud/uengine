#pragma once

#include <entt/entt.hpp>

namespace ue
{
	class editor 
	{
		friend class application;
	protected:
		entt::registry* registry;

		virtual void on_gui() { }
	};
}