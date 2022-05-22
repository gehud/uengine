#pragma once

#include "uengine/assertion.h"

namespace ue 
{
	enum class vertex_attribute_format
	{
		bool1,
		int1,
		int2,
		int3,
		int4,
		float1,
		float2,
		float3,
		float4,
		matrix3x3,
		matrix4x4,
	};

	static unsigned int get_vertex_attribute_format_size(vertex_attribute_format format) 
	{
		switch (format)
		{
			case vertex_attribute_format::bool1:		return 1;
			case vertex_attribute_format::int1:			return 4;
			case vertex_attribute_format::int2:			return 4 * 2;
			case vertex_attribute_format::int3:			return 4 * 3;
			case vertex_attribute_format::int4:			return 4 * 4;
			case vertex_attribute_format::float1:		return 4;
			case vertex_attribute_format::float2:		return 4 * 2;
			case vertex_attribute_format::float3:		return 4 * 3;
			case vertex_attribute_format::float4:		return 4 * 4;
			case vertex_attribute_format::matrix3x3:	return 4 * 3 * 3;
			case vertex_attribute_format::matrix4x4:	return 4 * 4 * 4;
		}
	}

	static unsigned int get_vertex_attribute_format_dimension(vertex_attribute_format format) 
	{
		switch (format)
		{
			case vertex_attribute_format::bool1:		return 1;
			case vertex_attribute_format::int1:			return 1;
			case vertex_attribute_format::int2:			return 2;
			case vertex_attribute_format::int3:			return 3;
			case vertex_attribute_format::int4:			return 4;
			case vertex_attribute_format::float1:		return 1;
			case vertex_attribute_format::float2:		return 2;
			case vertex_attribute_format::float3:		return 3;
			case vertex_attribute_format::float4:		return 4;
			case vertex_attribute_format::matrix3x3:	return 3 * 3;
			case vertex_attribute_format::matrix4x4:	return 4 * 4;
		}
	}

	class vertex_attribute_descriptor
	{
	private:
		vertex_attribute_format _format;
		const char* _name;
		unsigned int _size;
		unsigned int _dimension;
		unsigned int _offset = 0;
		bool _normalized;
	public:
		vertex_attribute_descriptor(vertex_attribute_format format, const char* name, bool normalized = false)
			: _format(format), _name(name), _size(get_vertex_attribute_format_size(format)),
				_dimension(get_vertex_attribute_format_dimension(format)), _normalized(normalized) { }

		vertex_attribute_format get_format() const { return _format; }

		void set_format(vertex_attribute_format value) 
		{ 
			_format = value; 
			_size = get_vertex_attribute_format_size(_format);
			_dimension = get_vertex_attribute_format_dimension(_format);
		}

		const char* get_name() const { return _name; }

		void set_name(const char* value) { _name = value; }

		unsigned int get_size() const { return _size; }

		unsigned int get_dimension() const { return _dimension; }

		bool is_normalized() const { return _normalized; }

		void set_normalization(bool value) { _normalized = value; }

		unsigned int get_offet() const { return _offset; }

		void set_offet(unsigned int value) { _offset = value; }
	};
}