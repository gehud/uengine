#include "uengine/rendering/gl.h"

namespace ue 
{
	std::shared_ptr<graphics_api> gl::_api = std::shared_ptr<graphics_api>(graphics_api::create());
}