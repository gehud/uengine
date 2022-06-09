#pragma once

#include "uengine/rendering/graphics_api_type.h"

namespace ue 
{
	class graphics final 
	{
	private:
		static graphics_api_type _api_type;
	public:
		static graphics_api_type get_api() noexcept { return _api_type; }
	};
}