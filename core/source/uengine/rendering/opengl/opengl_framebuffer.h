#pragma once

#include "uengine/rendering/framebuffer.h"

namespace ue 
{
	class opengl_framebuffer : public framebuffer 
	{
	private:
		unsigned int _id;
		framebuffer_descriptor _descriptor;
		unsigned int _color_buffer_id;
		unsigned int _depth_buffer_id;
	public:
		opengl_framebuffer(const framebuffer_descriptor& descriptor);

		~opengl_framebuffer();

		int get_width() const override { return _descriptor.width; }
		int get_height() const override { return _descriptor.height; }

		int get_color_buffer_id() const override { return static_cast<int>(_color_buffer_id); }
		int get_depth_buffer_id() const override { return static_cast<int>(_depth_buffer_id); }

		void bind() override;
		void unbind() override;
	};
}