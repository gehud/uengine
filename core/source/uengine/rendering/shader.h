#pragma once

#include "uengine/core/memory.h"
#include "uengine/math/vector2.h"
#include "uengine/math/vector3.h"
#include "uengine/math/vector4.h"
#include "uengine/math/matrix4x4.h"
#include "uengine/rendering/color.h"

#include <memory>

namespace ue 
{
	class shader 
	{
	public:
		static reference<shader> create(const char* path);
		static reference<shader> create(const char* vertex_source, const char* fragment_source);

		virtual ~shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_int(const char* name, int value) = 0;
		virtual void set_float(const char* name, float value) = 0;
		virtual void set_vector2(const char* name, const vector2& value) = 0;
		virtual void set_vector3(const char* name, const vector3& value) = 0;
		virtual void set_vector4(const char* name, const vector4& value) = 0;
		virtual void set_color(const char* name, const color& value) = 0;
		virtual void set_matrix4x4(const char* name, const matrix4x4& value) = 0;
	};
}