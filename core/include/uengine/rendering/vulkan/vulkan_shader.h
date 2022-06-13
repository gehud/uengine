#pragma once

#include "uengine/rendering/shader.h"

namespace ue 
{
	class vulkan_shader : public shader
	{
	public:
		vulkan_shader(const char* path);
		vulkan_shader(const char* vertex_source, const char* fragment_source);

		~vulkan_shader();

		void bind() const override { }
		void unbind() const override { }

		void set_int(const char* name, int value) override { }
		void set_float(const char* name, float value) override { }
		void set_vector2(const char* name, const vector2& value) override { }
		void set_vector3(const char* name, const vector3& value) override { }
		void set_vector4(const char* name, const vector4& value) override { }
		void set_color(const char* name, const color& value) override { }
		void set_matrix4x4(const char* name, const matrix4x4& value) override { }
	};
}