#pragma once

#include <math.h>

namespace ue {
	class math final {
	public:
		static const float pi;
	public:
		static float abs(float x) { return fabsf(x); }
		static float sqrt(float x) { return sqrtf(x); }

		static float radians(float degrees) { return degrees * (pi / 180.0f); }
		static float degrees(float radians) { return radians * (180.0f / pi); }
	private:
		math() = default;
	};
}