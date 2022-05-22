#pragma once

#include "uengine/rendering/frame_buffer.h"

namespace ue 
{
	class opengl_frame_buffer : public frame_buffer 
	{
	private:
		unsigned int _id;
		frame_buffer_descriptor _descriptor;
		unsigned int _color_buffer_id;
		unsigned int _depth_buffer_id;
	public:
		opengl_frame_buffer(const frame_buffer_descriptor& descriptor);

		~opengl_frame_buffer();

		int get_width() const override { return _descriptor.width; }
		int get_height() const override { return _descriptor.height; }

		int get_color_buffer_id() const override { return static_cast<int>(_color_buffer_id); }
		int get_depth_buffer_id() const override { return static_cast<int>(_depth_buffer_id); }

		void bind() override;
		void unbind() override;
	};
}