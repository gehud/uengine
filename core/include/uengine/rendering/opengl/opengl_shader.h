#pragma once

#include "uengine/rendering/shader.h"

#include <glad/glad.h>

#include <unordered_map>

namespace ue
{
	class opengl_shader : public shader 
	{
	private:
		unsigned int _id;
	public:
		opengl_shader(const char* path);
		opengl_shader(const char* vertex_source, const char* fragment_soruce);

		~opengl_shader();

		void bind() const override;
		void unbind() const override;

		void set_int(int value, const char* name) override;
		void set_float(float value, const char* name) override;
		void set_float2(const glm::vec2& value, const char* name) override;
		void set_float3(const glm::vec3& value, const char* name) override;
		void set_float4(const glm::vec4& value, const char* name) override;
		void set_mat3(const glm::mat3& value, const char* name) override;
		void set_mat4(const glm::mat4& value, const char* name) override;
	private:
		void compile(const std::unordered_map<GLenum, std::string>& shader_sources);
	};
}