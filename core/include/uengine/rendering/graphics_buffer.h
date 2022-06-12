#pragma once

#include "uengine/core/memory.h"

namespace ue 
{
	class graphics_buffer 
	{
	public:
		enum target 
		{
			index,
			vertex,
		};

		static reference<graphics_buffer> create(target target, int count, int stride);

		virtual ~graphics_buffer() = default;

		virtual target get_target() const = 0;
		virtual int get_count() const = 0;
		virtual int get_stride() const = 0;

		virtual void set_data(const void* value) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}