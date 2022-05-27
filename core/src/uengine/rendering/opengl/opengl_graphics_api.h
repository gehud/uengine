#pragma once

#include "uengine/rendering/graphics_api.h"

namespace ue 
{
	class opengl_graphics_api : public graphics_api 
	{
	public:
		void init() override;

		void clear_color(float r, float g, float b, float a) override;

		void clear() override;

		int get_triangles_mode() override;

		void draw_elements(int mode, int count, int type) override;

		void viewport(int x, int y, int width, int height) override;
	};
}