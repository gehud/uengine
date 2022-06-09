#pragma once

#include "uengine/core/component.h"
#include "uengine/rendering/color.h"

namespace ue 
{
	enum class light_type 
	{
		directional,
		point,
		spot,
	};

	class light : public component 
	{
	private:
		light_type _type = light_type::directional;
		color _color = color::white;
		float _intensity = 1.0f;
	public:
		light(const entity& entity) : component(entity) { }

		color get_color() const { return _color; }
		void set_color(const color& value) { _color = value; }

		float get_intensity() const { return _intensity; }
		void set_intensity(float value) { _intensity = value; }
	};
}