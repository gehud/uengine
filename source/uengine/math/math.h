#pragma once

#include <cmath>
#include <limits>

namespace ue {
	class math final {
	public:
		math() = delete;

		static constexpr float pi = 3.14159265358979323846;
		static constexpr float epsilon = std::numeric_limits<float>::epsilon();
		static constexpr float infinity = std::numeric_limits<float>::infinity();

		static float abs(float x) { return fabsf(x); }
		static float sqrt(float x) { return sqrtf(x); }

		static float min(float x, float y) { return fminf(x, y); }
		static float max(float x, float y) { return fmaxf(x, y); }
		static float clamp(float x, float min, float max) { return math::min(math::max(x, min), max); }

		static float sin(float x) { return sinf(x); }
		static float asin(float x) { return asinf(x); }
		static float cos(float x) { return cosf(x); }
		static float acos(float x) { return acosf(x); }
		static float tan(float x) { return tanf(x); }
		static float atan(float x) { return atanf(x); }
		static float atan2(float x, float y) { return atan2f(x, y); }

		static float radians(float degrees) { return degrees * (pi / 180.0f); }
		static float degrees(float radians) { return radians * (180.0f / pi); }
	};
}