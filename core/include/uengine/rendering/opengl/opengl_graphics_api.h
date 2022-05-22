#pragma once

#include "uengine/rendering/graphics_api.h"

namespace ue 
{
	class opengl_graphics_api : public graphics_api 
	{
	public:
		void init() const override;

		void clear_color(float r, float g, float b, float a) const override;

		void clear() const override;

		int get_triangles_mode() const override;

		void draw_elements(int mode, int count, int type) const override;

		void viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const override;
	};
}