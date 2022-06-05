#pragma once

#include "uengine/core/script.h"
#include "uengine/core/system.h"

#include <type_traits>

namespace ue 
{
	struct script_handle final
	{
		static void on_start(script& script) 
		{
			script.on_start();
		}

		static void on_update(script& script)
		{
			script.on_update();
		}
	};

	template<typename t, typename std::enable_if<std::is_base_of<script, t>::value, bool>::type = true>
	class script_system : public system
	{
		friend class script_manager;
	protected:
		void on_start() override 
		{
			get_registry().view<t>().each([](auto& script) { script_handle::on_start(static_cast<ue::script&>(script)); });
		}

		void on_update() override 
		{
			get_registry().view<t>().each([](auto& script) { script_handle::on_update(static_cast<ue::script&>(script)); });
		}
	};
}