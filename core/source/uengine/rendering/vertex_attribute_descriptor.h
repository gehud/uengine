#pragma once

#include "uengine/core/assertion.h"

namespace ue 
{
	enum class vertex_attribute_format
	{
		float16,
		float32,
		int8,
		int16,
		int32,
		uint8,
		uint16,
		uint32
	};

	static int get_vertex_attribute_format_size(vertex_attribute_format format) 
	{
		switch (format)
		{
		case vertex_attribute_format::float16: return 2;
		case vertex_attribute_format::float32: return 4;
		case vertex_attribute_format::int8: return 1;
		case vertex_attribute_format::int16: return 2;
		case vertex_attribute_format::int32: return 4;
		case vertex_attribute_format::uint8: return 1;
		case vertex_attribute_format::uint16: return 2;
		case vertex_attribute_format::uint32: return 4;
		}

		UE_CORE_ASSERT(false, "Unknown format.");
		return 0;
	}

	struct vertex_attribute_descriptor
	{
		const char* name;
		vertex_attribute_format format;
		int dimension;
		bool normalized;
	public:
		vertex_attribute_descriptor(const char* name, vertex_attribute_format format = vertex_attribute_format::float32, int dimension = 3, bool normalized = false) 
			: name(name), format(format), dimension(dimension), normalized(normalized) { }

		int get_size() const { return get_vertex_attribute_format_size(format) * dimension; }
	};
}