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

		void set_int(const char* name, int value) override;
		void set_float(const char* name, float value) override;
		void set_vector2(const char* name, const vector2& value) override;
		void set_vector3(const char* name, const vector3& value) override;
		void set_vector4(const char* name, const vector4& value) override;
		void set_color(const char* name, const color& value) override;
		void set_matrix4x4(const char* name, const matrix4x4& value) override;
	private:
		void compile(const std::unordered_map<GLenum, std::string>& shader_sources);
	};
}