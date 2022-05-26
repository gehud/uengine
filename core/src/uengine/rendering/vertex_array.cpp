#include "vertex_array.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_vertex_array.h"

namespace ue 
{
	std::shared_ptr<vertex_array> vertex_array::create()
	{
		switch (graphics::get_api())
		{
		case graphics_apis::opengl: return std::shared_ptr<vertex_array>(new opengl_vertex_array());
		}
	}
}