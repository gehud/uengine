#include "shader.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_shader.h"

namespace ue 
{
	std::shared_ptr<shader> shader::create(const char* path)
	{
		switch (graphics::get_api())
		{
			case graphics_api_type::opengl: return std::shared_ptr<shader>(new opengl_shader(path));
		}
	}

	std::shared_ptr<shader> shader::create(const char* vertex_source, const char* fragment_source)
	{
		switch (graphics::get_api())
		{
			case graphics_api_type::opengl: 
				return std::shared_ptr<shader>(new opengl_shader(vertex_source, fragment_source));
		}
	}
}