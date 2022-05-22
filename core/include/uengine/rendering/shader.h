#pragma once

#include <memory>

#include <glm/glm.hpp>

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
		virtual void set_float2(const glm::vec2& value, const char* name) = 0;
		virtual void set_float3(const glm::vec3& value, const char* name) = 0;
		virtual void set_float4(const glm::vec4& value, const char* name) = 0;
		virtual void set_mat3(const glm::mat3& value, const char* name) = 0;
		virtual void set_mat4(const glm::mat4& value, const char* name) = 0;
	};
}