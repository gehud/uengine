#pragma once

#include "uengine/math/vector2.h"
#include "uengine/math/vector3.h"
#include "uengine/math/vector4.h"
#include "uengine/math/matrix4x4.h"

#include <memory>

namespace ue 
{
	class shader 
	{
	public:
		static std::shared_ptr<shader> create(const char* path);
		static std::shared_ptr<shader> create(const char* vertex_source, const char* fragment_source);

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_int(int value, const char* name) = 0;
		virtual void set_float(float value, const char* name) = 0;
		virtual void set_vector2(const vector2& value, const char* name) = 0;
		virtual void set_vector3(const vector3& value, const char* name) = 0;
		virtual void set_vector4(const vector4& value, const char* name) = 0;
		virtual void set_matrix4x4(const matrix4x4& value, const char* name) = 0;
	};
}