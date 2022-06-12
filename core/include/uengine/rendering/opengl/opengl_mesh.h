#pragma once

#include "uengine/rendering/mesh.h"

#include <vector>

namespace ue 
{
	class opengl_mesh : public mesh 
	{
	private:
		unsigned int _id;
		vertex_buffer_layout _vertex_buffer_layout;
		std::vector<reference<graphics_buffer>> _vertex_buffers;
		index_format _index_format = index_format::uint32;
		reference<graphics_buffer> _index_buffer;
	public:
		opengl_mesh();

		~opengl_mesh();

		const reference<graphics_buffer>& get_vertex_buffer(int index) const override { return _vertex_buffers[index]; }

		const reference<graphics_buffer>& get_index_buffer() const override { return _index_buffer; }

		void set_vertex_buffer_params(int count, const vertex_buffer_layout& layout) override;

		void set_vertex_buffer_data(const void* value, int index) override;

		void set_index_buffer_params(int count, index_format format) override;

		void set_index_buffer_data(const void* value) override;

		index_format get_index_format() const override { return _index_format; }

		void bind() const override;
		void unbind() const override;
	};
}