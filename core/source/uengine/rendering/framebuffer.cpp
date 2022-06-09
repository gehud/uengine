#include "uengine/rendering/framebuffer.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_framebuffer.h"

namespace ue 
{
	std::shared_ptr<framebuffer> framebuffer::create(const framebuffer_descriptor& descriptor)
	{
		switch (graphics::get_api())
		{
		case graphics_api_type::opengl:	
			return std::shared_ptr<framebuffer>(new opengl_framebuffer(descriptor));
		}
	}

}