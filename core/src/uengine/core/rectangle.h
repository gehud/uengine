#pragma once

#include "uengine/core/assertion.h"
#include "uengine/math/vector2.h"

namespace ue 
{
	struct rectangle 
	{
		static const rectangle zero;

		float x = 0.0f;
		float y = 0.0f;
		float width = 0.0f;
		float height = 0.0f;

		rectangle() = default;
		rectangle(float x, float y, float width, float height) 
		{
			UE_CORE_ASSERT(x >= 0, "X out of range.");
			this->x = x;
			UE_CORE_ASSERT(y >= 0, "Y out of range.");
			this->y = y;
			UE_CORE_ASSERT(width >= 0, "Width out of range.");
			this->width = width;
			UE_CORE_ASSERT(height >= 0, "Height out of range.");
			this->height = height;
		}

		rectangle(const vector2& position, const vector2& size) 
		{
			UE_CORE_ASSERT(position >= vector2::zero, "Position out of range.");
			x = position.x;
			y = position.y;
			UE_CORE_ASSERT(size >= vector2::zero, "Size out of range.");
			width = size.x;
			height = size.y;
		}

		static rectangle get_zero() { return zero; }

		vector2 get_position() const { return vector2(x, y); }
		void set_position(const vector2& value) { x = value.x; y = value.y; }

		float get_x_min() const { return x; }
		float get_x_max() const { return x + width; }
		float get_y_min() const { return y; }
		float get_y_max() const { return y + height; }
	};
}