#pragma once

#include "uengine/assertion.h"

#include <glm/glm.hpp>

namespace ue 
{
	struct vector2 
	{
		static const vector2 one;
		static const vector2 zero;
		static const vector2 right;
		static const vector2 left;
		static const vector2 up;
		static const vector2 down;

		float x = 0.0f;
		float y = 0.0f;

		vector2(float x, float y) : x(x), y(y) { }

		vector2(const glm::vec2 vector) : x(vector.x), y(vector.y) { }

		float get_magnitude() const
		{
			return glm::length((glm::vec2)*this);
		}

		vector2 get_normalized() const 
		{
			return glm::normalize((glm::vec2)*this);
		}

		void normalize() 
		{
			*this = get_normalized();
		}

		operator glm::vec2() const noexcept { return glm::vec2(x, y); }

		float operator [] (int index) const
		{
			UE_CORE_ASSERT(index > -1 && index < 2, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			}
		}

		float& operator [] (int index)
		{
			UE_CORE_ASSERT(index > -1 && index < 2, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			}
		}
	};
}