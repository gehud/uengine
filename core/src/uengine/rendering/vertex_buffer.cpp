#include "uengine/rendering/vertex_buffer.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_vertex_buffer.h"

namespace ue 
{
	std::shared_ptr<vertex_buffer> vertex_buffer::create(const void* data, int count, int stride)
	{
		switch (graphics::get_api())
		{
			case graphics_apis::opengl: 
				return std::shared_ptr<vertex_buffer>(new opengl_vertex_buffer(data, count, stride));
		}
	}
}