#pragma once

namespace ue 
{
	class graphics_api 
	{
	public:
		static graphics_api* create();

		virtual void init() const = 0;

		virtual void clear_color(float r, float g, float b, float a) const = 0;

		virtual void clear() const = 0;

		virtual int get_triangles_mode() const = 0;

		virtual void draw_elements(int mode, int count, int type) const = 0;

		virtual void viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const = 0;
	};
}