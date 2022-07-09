#include "graphics.h"

namespace ue {
	graphics_api_type graphics::_api_type = graphics_api_type::opengl;
	graphics_api* graphics::_api = nullptr;

	void graphics::initialize() {
		_api = new graphics_api();
	}

	void graphics::terminate() {
		delete _api;
	}
}