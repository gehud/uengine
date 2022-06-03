#pragma once

#include "uengine/core/rectangle.h"
#include "uengine/core/delegates.h"

namespace ue 
{
	class editor_gui final
	{
	public:
		static rectangle window(const rectangle& rectangle, const ifunction<void>& function, const char* name);
	private:
		editor_gui() = default;
	};
}