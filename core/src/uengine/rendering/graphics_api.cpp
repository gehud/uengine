#include "uengine/rendering/graphics_api.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_graphics_api.h"

namespace ue 
{
	graphics_api* graphics_api::create()
	{
		switch (graphics::get_api())
		{
		case graphics_apis::opengl: return new opengl_graphics_api();
		}
	}
}