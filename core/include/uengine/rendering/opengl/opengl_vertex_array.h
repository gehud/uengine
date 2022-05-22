#pragma once

#include "uengine/rendering/vertex_array.h"

namespace ue 
{
	class opengl_vertex_array : public vertex_array 
	{
	private:
		unsigned int _id;
	public:
		opengl_vertex_array();
		~opengl_vertex_array();

		void bind() const override;
		void unbind() const override;
	};
}