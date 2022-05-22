#pragma once

#include "uengine/rendering/texture_2d.h"

namespace ue 
{
	class opengl_texture_2d : public texture_2d 
	{
	private:
		unsigned int _id;
		int _width, _height;
	public:
		opengl_texture_2d(const char* path);

		~opengl_texture_2d();

		int get_width() const override { return _width; }
		int get_height() const override { return _height; }

		void bind(int slot) const override;
	};
}