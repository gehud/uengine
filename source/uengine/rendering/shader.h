#pragma once

#include "uengine/core/memory.h"
#include "uengine/core/assertion.h"
#include "uengine/math/vector2.h"
#include "uengine/math/vector3.h"
#include "uengine/math/vector4.h"
#include "uengine/math/matrix4x4.h"

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <unordered_map>

namespace ue {
	static std::string get_file_source(const char* path) {
		std::string res;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		UE_CORE_ASSERT(in, "Could not open file {0}.", path);
		in.seekg(0, std::ios::end);
		res.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&res[0], res.size());
		in.close();
		return res;
	}

	static GLenum string_to_shader_type(const char* value) {
		if (!strcmp(value, "vertex"))
			return GL_VERTEX_SHADER;
		else if (!strcmp(value, "fragment") || !strcmp(value, "pixel"))
			return GL_FRAGMENT_SHADER;
		UE_CORE_ASSERT(false, "Unknown shader type: {0}.", value);
		return 0;
	}

	static const char* shader_type_to_string(GLenum type) {
		if (type == GL_VERTEX_SHADER)
			return "Vertex";
		else if (type == GL_FRAGMENT_SHADER)
			return "Fragment";
		return "Unknown";
	}

	static std::unordered_map<GLenum, std::string> get_shader_sources(const std::string& file_source) {
		std::unordered_map<GLenum, std::string> res;
		const char* type_token = "#type";
		size_t type_token_length = strlen(type_token);
		size_t position = file_source.find(type_token, 0);

		while (position != std::string::npos) {
			size_t eol_pos = file_source.find_first_of("\r\n", position);
			UE_CORE_ASSERT(eol_pos != std::string::npos, "Syntax error.");
			size_t begin = file_source.find_first_not_of(' ', position + type_token_length + 1);
			std::string type = file_source.substr(begin, eol_pos - begin);
			UE_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Invalid shader type.");

			size_t next_line_pos = file_source.find_first_not_of("\r\n", eol_pos);
			position = file_source.find(type_token, next_line_pos);
			res[string_to_shader_type(type.c_str())] = file_source.substr(next_line_pos,
				position - (next_line_pos == std::string::npos ? file_source.size() - 1 : next_line_pos));
		}

		return res;
	}

	class shader {
	public:
		shader(const char* path) {
			compile(get_shader_sources(get_file_source(path)));
		}

		shader(const char* vertex_source, const char* fragment_source) {
			std::unordered_map<GLenum, std::string> shader_sources;
			shader_sources[GL_VERTEX_SHADER] = vertex_source;
			shader_sources[GL_FRAGMENT_SHADER] = fragment_source;
			compile(shader_sources);
		}

		~shader() {
			glDeleteProgram(_id);
		}

		static reference<shader> create(const char* path) {
			return reference<shader>(new shader(path));
		}

		static reference<shader> create(const char* vertex_source, const char* fragment_source) {
			return reference<shader>(new shader(vertex_source, fragment_source));
		}

		void bind() const {
			glUseProgram(_id);
		}

		void unbind() const {
			glUseProgram(0);
		}

		virtual void set_int(const char* name, int32 value) {
			GLint location = glGetUniformLocation(_id, name);
			glUniform1i(location, value);
		}

		virtual void set_float(const char* name, float value) {
			GLint location = glGetUniformLocation(_id, name);
			glUniform1f(location, value);
		}

		virtual void set_vector2(const char* name, const vector2& value) {
			GLint location = glGetUniformLocation(_id, name);
			glUniform2f(location, value.x, value.y);
		}

		virtual void set_vector3(const char* name, const vector3& value) {
			GLint location = glGetUniformLocation(_id, name);
			glUniform3f(location, value.x, value.y, value.z);
		}

		virtual void set_vector4(const char* name, const vector4& value) {
			GLint location = glGetUniformLocation(_id, name);
			glUniform4f(location, value.x, value.y, value.z, value.w);
		}

		virtual void set_matrix4x4(const char* name, const matrix4x4& value) {
			GLint location = glGetUniformLocation(_id, name);
			glUniformMatrix4fv(location, 1, GL_FALSE, value.to_array());
		}

		virtual void set_matrix4x4(const char* name, const glm::mat4& value) {
			GLint location = glGetUniformLocation(_id, name);
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
	private:
		uint32 _id;
	private:
		void compile(const std::unordered_map<GLenum, std::string>& shader_sources) {
			_id = glCreateProgram();
			std::vector<GLuint> shaders(shader_sources.size());
			for (auto& kv : shader_sources) {
				GLenum type = kv.first;
				const std::string& source = kv.second;

				GLuint shader = glCreateShader(type);
				const GLchar* gl_source = (const GLchar*)source.c_str();
				glShaderSource(shader, 1, &gl_source, 0);

				glCompileShader(shader);

				GLint is_compiled = 0;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
				if (is_compiled == GL_FALSE) {
					GLint max_length = 0;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

					std::vector<GLchar> info_log(max_length);
					glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

					glDeleteShader(shader);
					glDeleteProgram(_id);

					UE_CORE_ASSERT(false, "{0} shader compilation failure: {1}", shader_type_to_string(type), info_log.data());

					return;
				}
				glAttachShader(_id, shader);
				shaders.push_back(shader);
			}

			glLinkProgram(_id);

			GLint is_linked = 0;
			glGetProgramiv(_id, GL_LINK_STATUS, (int*)&is_linked);
			if (is_linked == GL_FALSE) {
				GLint max_length = 0;
				glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &max_length);

				std::vector<GLchar> info_log(max_length);
				glGetProgramInfoLog(_id, max_length, &max_length, &info_log[0]);

				glDeleteProgram(_id);
				for (auto shader : shaders)
					glDeleteShader(shader);

				UE_CORE_ASSERT(false, "Shader linking failure: {0}", info_log.data());

				return;
			}

			for (auto shader : shaders)
				glDetachShader(_id, shader);
		}
	};
}