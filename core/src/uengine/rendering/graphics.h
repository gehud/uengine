#pragma once

#include "uengine/rendering/graphics_apis.h"

namespace ue 
{
	class graphics final 
	{
	private:
		static graphics_apis _api;
	public:
		static graphics_apis get_api() noexcept { return _api; }
	};
}