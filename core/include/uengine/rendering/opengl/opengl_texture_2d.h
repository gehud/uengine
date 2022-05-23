#pragma once

#include "uengine/rendering/texture_2d.h"

namespace ue 
{
	class opengl_texture_2d : public texture_2d 
	{
	private:
		unsigned int _id;
		int _width, _height;
		texture_wrap_mode _wrap_mode;
		texture_filter_mode _filter_mode;
	public:
		opengl_texture_2d(const char* path);

		~opengl_texture_2d();

		int get_width() const override { return _width; }
		int get_height() const override { return _height; }

		texture_wrap_mode get_wrap_mode() const override { return _wrap_mode; }
		void set_wrap_mode(texture_wrap_mode value) override;

		texture_filter_mode get_filter_mode() const override { return _filter_mode; }
		void set_filter_mode(texture_filter_mode value) override;

		void bind(int slot) const override;
	};
}