#include "gl.h"

namespace ue 
{
	std::unique_ptr<graphics_api> gl::_api = std::unique_ptr<graphics_api>(graphics_api::create());
}