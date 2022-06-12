#pragma once

#include "uengine/rendering/graphics_buffer.h"

namespace ue 
{
	class opengl_graphics_buffer : public graphics_buffer
	{
	private:
		target _target;
		int _count;
		int _stride;
		unsigned int _id;
	public:
		opengl_graphics_buffer(target target, int count, int stride);

		~opengl_graphics_buffer();

		target get_target() const override { return _target; }
		int get_count() const override { return _count; }
		int get_stride() const override { return _stride; }

		void set_data(const void* value) override;

		void bind() const override;
		void unbind() const override;
	};
}