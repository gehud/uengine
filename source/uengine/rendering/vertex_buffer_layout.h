#pragma once

#include "vertex_attribute_descriptor.h"

#include <vector>

namespace ue {
	class vertex_buffer_layout {
	public:
		vertex_buffer_layout() = default;

		vertex_buffer_layout(const std::initializer_list<vertex_attribute_descriptor>& descriptors)
			: _descriptors(descriptors) {
			calculate_stride();
		}

		uint32 get_stride() const { return _stride; }

		std::vector<vertex_attribute_descriptor>::iterator begin() { return _descriptors.begin(); }
		std::vector<vertex_attribute_descriptor>::iterator end() { return _descriptors.end(); }

		std::vector<vertex_attribute_descriptor>::const_iterator begin() const { return _descriptors.begin(); }
		std::vector<vertex_attribute_descriptor>::const_iterator end() const { return _descriptors.end(); }
	private:
		std::vector<vertex_attribute_descriptor> _descriptors;
		uint32 _stride = 0;
	private:
		void calculate_stride() {
			_stride = 0;
			for (const auto& element : _descriptors)
				_stride += element.get_size();
		}
	};
}