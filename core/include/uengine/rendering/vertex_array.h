#pragma once

#include <memory>

namespace ue 
{
	class vertex_array 
	{
	public:
		static std::shared_ptr<vertex_array> create();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}