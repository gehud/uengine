#pragma once

#include "uengine/math/math.h"
#include "uengine/core/types.h"
#include "uengine/core/assertion.h"

#include <ostream>

namespace ue {
	struct vector3 {
		static const vector3 one;
		static const vector3 zero;
		static const vector3 right;
		static const vector3 left;
		static const vector3 up;
		static const vector3 down;
		static const vector3 forward;
		static const vector3 back;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		vector3() = default;
		
		vector3(float x, float y, float z) : x(x), y(y), z(z) { }

		static vector3 get_one() { return one; }
		static vector3 get_zero() { return zero; }
		static vector3 get_right() { return right; }
		static vector3 get_left() { return left; }
		static vector3 get_up() { return up; }
		static vector3 get_down() { return down; }
		static vector3 get_forward() { return forward; }
		static vector3 get_back() { return back; }

		static float dot(const vector3& a, const vector3& b) {
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}

		static float angle(const vector3& a, const vector3& b) {
			return math::degrees(math::acos(dot(a, b) / ((a.get_magnitude() * b.get_magnitude()))));
		}

		static vector3 sin(const vector3& vector) {
			return vector3(math::sin(vector.x), math::sin(vector.y), math::sin(vector.z));
		}

		static vector3 cos(const vector3& vector) {
			return vector3(math::cos(vector.x), math::cos(vector.y), math::cos(vector.z));
		}

		float get_magnitude() const {
			return std::sqrtf(x * x + y * y + z * z);
		}

		vector3 get_normalized() const {
			float magnitude = get_magnitude();
			if (magnitude > 0)
				return vector3(x / magnitude, y / magnitude, z / magnitude);
			return zero;
		}

		void normalize() {
			*this = get_normalized();
		}

		float operator [] (uint32 index) const
		{
			UE_CORE_ASSERT(index <= 2, "Index out of range.");
			switch (index) {
				case 0: return x;
				case 1: return y;
				case 2: return z;
			}
		}

		float& operator [] (uint32 index) {
			UE_CORE_ASSERT(index <= 2, "Index out of range.");
			switch (index) {
				case 0: return x;
				case 1: return y;
				case 2: return z;
			}
		}

		vector3& operator += (const vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		vector3& operator -= (const vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
	};

	inline vector3 operator + (const vector3& vector) {
		return vector3(vector.x, vector.y, vector.z);
	}

	inline vector3 operator + (const vector3& left, const vector3& right) {
		return vector3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	inline vector3 operator - (const vector3& left, const vector3& right) {
		return vector3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	inline vector3 operator - (const vector3& vector) {
		return vector3(-vector.x, -vector.y, -vector.z);
	}

	inline vector3 operator * (const vector3& vector, float number) {
		return vector3(vector.x * number, vector.y * number, vector.z * number);
	}

	inline vector3 operator / (const vector3& vector, float number) {
		return vector3(vector.x / number, vector.y / number, vector.z / number);
	}

	inline bool operator == (const vector3& left, const vector3& right) {
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	inline bool operator != (const vector3& left, const vector3& right) {
		return !(left == right);
	}

	inline std::ostream& operator << (std::ostream& ostream, const vector3& vector) {
		return ostream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	}
}