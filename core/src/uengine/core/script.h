#pragma once

#include "uengine/core/component.h"

namespace ue 
{
	class script : public component
	{
		friend class script_handle;
	public:
		script(const entity& entity) : component(entity) { }
	protected:
		virtual void on_start() { }
		virtual void on_update() { }
	};
}