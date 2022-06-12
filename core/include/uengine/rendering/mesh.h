#pragma once

#include "uengine/core/memory.h"
#include "uengine/rendering/index_format.h"
#include "uengine/rendering/graphics_buffer.h"
#include "uengine/rendering/vertex_buffer_layout.h"

namespace ue 
{
	class mesh 
	{
	public:
		static reference<mesh> create();

		virtual ~mesh() = default;

		virtual const reference<graphics_buffer>& get_vertex_buffer(int index) const = 0;

		virtual const reference<graphics_buffer>& get_index_buffer() const = 0;

		virtual void set_vertex_buffer_params(int count, const vertex_buffer_layout& layout) = 0;

		virtual void set_vertex_buffer_data(const void* value, int index = 0) = 0;

		virtual void set_index_buffer_params(int count, index_format format = index_format::uint32) = 0;

		virtual void set_index_buffer_data(const void* value) = 0;

		virtual index_format get_index_format() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}