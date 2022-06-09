#pragma once

namespace ue 
{
	class graphics_api 
	{
	public:
		static graphics_api* create();

		virtual void init() = 0;

		virtual void terminate() = 0;

		virtual void clear_color(float r, float g, float b, float a) = 0;

		virtual void clear() = 0;

		virtual int get_triangles_mode() = 0;

		virtual void draw_elements(int mode, int count, int type) = 0;

		virtual void viewport(int x, int y, int width, int height) = 0;
	};
}