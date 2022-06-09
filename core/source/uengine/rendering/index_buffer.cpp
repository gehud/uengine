#include "index_buffer.h"

#include "uengine/rendering/graphics.h"
#include "uengine/rendering/opengl/opengl_index_buffer.h"

namespace ue 
{
	std::shared_ptr<index_buffer> index_buffer::create(const unsigned char* indices, int count, int stride)
	{
		switch (graphics::get_api())
		{
			case graphics_api_type::opengl: 
				return std::shared_ptr<index_buffer>(new opengl_index_buffer(indices, count, stride));
		}
	}

	std::shared_ptr<index_buffer> index_buffer::create(const unsigned short* indices, int count, int stride)
	{
		switch (graphics::get_api())
		{
			case graphics_api_type::opengl:
				return std::shared_ptr<index_buffer>(new opengl_index_buffer(indices, count, stride));
		}
	}

	std::shared_ptr<index_buffer> index_buffer::create(const unsigned int* indices, int count, int stride)
	{
		switch (graphics::get_api())
		{
			case graphics_api_type::opengl:
				return std::shared_ptr<index_buffer>(new opengl_index_buffer(indices, count, stride));
		}
	}
}