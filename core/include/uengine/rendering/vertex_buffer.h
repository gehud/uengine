#pragma once

#include "uengine/rendering/vertex_buffer_layout.h"

#include <memory>

namespace ue 
{
	class vertex_buffer
	{
	public:
		static std::shared_ptr<vertex_buffer> create(const void* data, int count, int stride);

		virtual int get_count() const = 0;

		virtual int get_stride() const = 0;

		virtual const vertex_buffer_layout& get_layout() const = 0;
		virtual void set_layout(const vertex_buffer_layout& value) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}