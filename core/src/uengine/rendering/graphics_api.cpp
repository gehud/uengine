#include "graphics_api.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_graphics_api.h"
#include "uengine/rendering/vulkan/vulkan_graphics_api.h"

namespace ue 
{
	graphics_api* graphics_api::create()
	{
		switch (graphics::get_api())
		{
		case graphics_api_type::opengl: return new opengl_graphics_api();
		case graphics_api_type::vulkan: return new vulkan_graphics_api();
		}
	}
}