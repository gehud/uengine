#pragma once

#include "uengine/rendering/vertex_attribute_descriptor.h"

#include <vector>

namespace ue 
{
	class vertex_buffer_layout 
	{
	private:
		std::vector<vertex_attribute_descriptor> _descriptors;
		int _stride = 0;
	public:
		vertex_buffer_layout() = default;

		vertex_buffer_layout(const std::initializer_list<vertex_attribute_descriptor>& descriptors)
			: _descriptors(descriptors) { calculate_stride(); }

		int get_stride() const { return _stride; }

		std::vector<vertex_attribute_descriptor>::iterator begin() { return _descriptors.begin(); }
		std::vector<vertex_attribute_descriptor>::iterator end() { return _descriptors.end(); }

		std::vector<vertex_attribute_descriptor>::const_iterator begin() const { return _descriptors.begin(); }
		std::vector<vertex_attribute_descriptor>::const_iterator end() const { return _descriptors.end(); }
	private:
		void calculate_stride() 
		{
			_stride = 0;
			for (const auto& element : _descriptors)
				_stride += element.get_size();
		}
	};
}