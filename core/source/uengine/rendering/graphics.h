#pragma once

#include "uengine/rendering/gl.h"
#include "uengine/rendering/mesh.h"
#include "uengine/rendering/shader.h"
#include "uengine/rendering/graphics_api_type.h"

namespace ue 
{
	class graphics final 
	{
	private:
		static graphics_api_type _api_type;
	public:
		static graphics_api_type get_api() noexcept { return _api_type; }

		static void draw_mesh(const reference<mesh>& mesh) 
		{
			mesh->bind();
			gl::draw_elements(gl::get_triangles_mode(), mesh->get_index_buffer()->get_count(), mesh->get_index_format());
		}
	};
}