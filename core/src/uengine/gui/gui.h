#pragma once

#include "uengine/core/rectangle.h"
#include "uengine/core/delegates.h"

namespace ue 
{
	class gui final
	{
	private:

	public:
		static void window(const rectangle& rectangle, const ifunction<void>& function, const char* name);
	private:
		gui() = default;
	};
}