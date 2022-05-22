#include "uengine/rendering/frame_buffer.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_frame_buffer.h"

namespace ue 
{
	std::shared_ptr<frame_buffer> frame_buffer::create(const frame_buffer_descriptor& descriptor)
	{
		switch (graphics::get_api())
		{
		case graphics_apis::opengl:	
			return std::shared_ptr<frame_buffer>(new opengl_frame_buffer(descriptor));
		}
	}

}