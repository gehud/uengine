#include "uengine/rendering/texture_2d.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_texture_2d.h"

namespace ue 
{
	std::shared_ptr<texture_2d> texture_2d::create(const char* path)
	{
		switch (graphics::get_api())
		{
		case graphics_apis::opengl: return std::shared_ptr<texture_2d>(new opengl_texture_2d(path));
		}
	}

}