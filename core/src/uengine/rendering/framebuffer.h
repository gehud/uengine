#pragma once

#include "uengine/core/assertion.h"

#include <memory>

namespace ue 
{
	struct framebuffer_descriptor 
	{
		int width, height; 
		int samples;

		framebuffer_descriptor(int width, int height, int samples = 1) 
		{
			UE_CORE_ASSERT(width > -1, "Width out of range.");
			UE_CORE_ASSERT(height > -1, "Height out of range.");
			UE_CORE_ASSERT(samples > 0, "Samples out of range.");
			this->width = width;
			this->height = height;
			this->samples = samples;
		}
	};

	class framebuffer 
	{
	public:
		static std::shared_ptr<framebuffer> create(const framebuffer_descriptor& descriptor);

		virtual int get_width() const = 0;
		virtual int get_height() const = 0;

		virtual int get_color_buffer_id() const = 0;
		virtual int get_depth_buffer_id() const = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}