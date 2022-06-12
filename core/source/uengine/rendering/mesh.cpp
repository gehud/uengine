#include "uengine/rendering/mesh.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_mesh.h"

namespace ue 
{
	reference<mesh> mesh::create()
	{
		switch (graphics::get_api())
		{
		case graphics_api_type::opengl: return reference<mesh>(new opengl_mesh());
		}

		return reference<mesh>();
	}
}