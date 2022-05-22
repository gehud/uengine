#pragma once

#include "uengine/rendering/vertex_buffer.h"

namespace ue 
{
	class opengl_vertex_buffer : public vertex_buffer
	{
	private:
		unsigned int _id;
		vertex_buffer_layout _layout;
		int _count;
		int _stride;
	public:
		opengl_vertex_buffer(const void* data, int count, int stride);

		~opengl_vertex_buffer();

		int get_count() const override { return _count; }

		int get_stride() const override { return _stride; }

		const vertex_buffer_layout& get_layout() const override { return _layout; }
		void set_layout(const vertex_buffer_layout& value) override;

		void bind() const override;
		void unbind() const override;
	};
}