#pragma once

#include "uengine/rendering/graphics_api.h"

#include <memory>

namespace ue 
{
	class gl final
	{
	private:
		static std::unique_ptr<graphics_api> _api;
	public:
		static void init() { _api->init(); }

		static void clear_color(float r, float g, float b, float a) { _api->clear_color(r, g, b, a); }

		static void clear() { _api->clear(); }

		static int get_triangles_mode() { return _api->get_triangles_mode(); }

		static void draw_elements(int mode, int count, int type) { _api->draw_elements(mode, count, type); }

		static void viewport(int x, int y, int width, int height) { _api->viewport(x, y, width, height); }
	};
}