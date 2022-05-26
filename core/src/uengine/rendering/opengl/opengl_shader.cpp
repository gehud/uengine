#include "opengl_shader.h"

#include "uengine/core/assertion.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace ue 
{
	static std::string get_file_source(const char* path) 
	{
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

	static GLenum string_to_shader_type(const char* value) 
	{
		if (!strcmp(value, "vertex"))
			return GL_VERTEX_SHADER;
		else if (!strcmp(value, "fragment") || !strcmp(value, "pixel"))
			return GL_FRAGMENT_SHADER;
		UE_CORE_ASSERT(false, "Unknown shader type: {0}.", value);
		return 0;
	}

	static const char* shader_type_to_string(GLenum type)
	{
		if (type == GL_VERTEX_SHADER)
			return "Vertex";
		else if (type == GL_FRAGMENT_SHADER)
			return "Fragment";
		return "Unknown";
	}

	static std::unordered_map<GLenum, std::string> get_shader_sources(const std::string& file_source) 
	{
		std::unordered_map<GLenum, std::string> res;
		const char* type_token = "#type";
		size_t type_token_length = strlen(type_token);
		size_t position = file_source.find(type_token, 0);
		while (position != std::string::npos) 
		{
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

	opengl_shader::opengl_shader(const char* path)
	{
		compile(get_shader_sources(get_file_source(path)));
	}

	opengl_shader::opengl_shader(const char* vertex_source, const char* fragment_soruce)
	{
		std::unordered_map<GLenum, std::string> shader_sources;
		shader_sources[GL_VERTEX_SHADER] = vertex_source;
		shader_sources[GL_FRAGMENT_SHADER] = fragment_soruce;
		compile(shader_sources);
	}

	opengl_shader::~opengl_shader()
	{
		glDeleteProgram(_id);
	}

	void opengl_shader::bind() const
	{
		glUseProgram(_id);
	}

	void opengl_shader::unbind() const
	{
		glUseProgram(0);
	}

	void opengl_shader::set_int(int value, const char* name)
	{
		GLint location = glGetUniformLocation(_id, name);
		glUniform1i(location, value);
	}

	void opengl_shader::set_float(float value, const char* name)
	{
		GLint location = glGetUniformLocation(_id, name);
		glUniform1f(location, value);
	}

	void opengl_shader::set_float2(const glm::vec2& value, const char* name)
	{
		GLint location = glGetUniformLocation(_id, name);
		glUniform2f(location, value.x, value.y);
	}

	void opengl_shader::set_float3(const glm::vec3& value, const char* name)
	{
		GLint location = glGetUniformLocation(_id, name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void opengl_shader::set_float4(const glm::vec4& value, const char* name)
	{
		GLint location = glGetUniformLocation(_id, name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void opengl_shader::set_mat3(const glm::mat3& value, const char* name)
	{
		GLint location = glGetUniformLocation(_id, name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void opengl_shader::set_mat4(const glm::mat4& value, const char* name)
	{
		GLint location = glGetUniformLocation(_id, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void opengl_shader::compile(const std::unordered_map<GLenum, std::string>& shader_sources)
	{
		_id = glCreateProgram();
		std::vector<GLuint> shaders(shader_sources.size());
		for (auto& kv : shader_sources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* gl_source = (const GLchar*)source.c_str();
			glShaderSource(shader, 1, &gl_source, 0);

			glCompileShader(shader);

			GLint is_compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
			if (is_compiled == GL_FALSE)
			{
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
		if (is_linked == GL_FALSE)
		{
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
}