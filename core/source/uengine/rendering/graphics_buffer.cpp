#include "uengine/rendering/graphics_buffer.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_graphics_buffer.h"

namespace ue 
{
    reference<graphics_buffer> graphics_buffer::create(target target, int count, int stride)
    {
        switch (graphics::get_api())
        {
        case graphics_api_type::opengl: 
            return reference<graphics_buffer>(new opengl_graphics_buffer(target, count, stride));
        }

        return reference<graphics_buffer>();
    }
}