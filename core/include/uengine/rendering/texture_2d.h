#pragma once

#include "uengine/rendering/texture.h"

#include <memory>

namespace ue 
{
	class texture_2d : public texture 
	{
	public:
		static std::shared_ptr<texture_2d> create(const char* path);
	};
}