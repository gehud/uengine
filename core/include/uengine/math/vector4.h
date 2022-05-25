#pragma once

#include "uengine/assertion.h"

#include <glm/glm.hpp>

namespace ue
{
	struct vector4
	{
		static const vector4 one;
		static const vector4 zero;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

		vector4(const glm::vec4 vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) { }

		float get_magnitude() const
		{
			return glm::length((glm::vec4)*this);
		}

		vector4 get_normalized() const
		{
			return glm::normalize((glm::vec4)*this);
		}

		void normalize()
		{
			*this = get_normalized();
		}

		operator glm::vec4() const noexcept { return glm::vec4(x, y, z, w); }

		float operator [] (int index) const
		{
			UE_CORE_ASSERT(index > -1 && index < 4, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			}
		}

		float& operator [] (int index)
		{
			UE_CORE_ASSERT(index > -1 && index < 3, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			}
		}
	};
}