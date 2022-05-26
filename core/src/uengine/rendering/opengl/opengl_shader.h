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
		void set_vector2(const vector2& value, const char* name) override;
		void set_vector3(const vector3& value, const char* name) override;
		void set_vector4(const vector4& value, const char* name) override;
		void set_matrix4x4(const matrix4x4& value, const char* name) override;
	private:
		void compile(const std::unordered_map<GLenum, std::string>& shader_sources);
	};
}