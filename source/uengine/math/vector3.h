#pragma once

#include "uengine/math/math.h"
#include "uengine/math/vector2.h"
#include "uengine/core/assertion.h"

#include <glm/vec3.hpp>

#include <ostream>

namespace ue {
	struct vector3 {
		static const vector3 zero;
		static const vector3 one;
		static const vector3 left;
		static const vector3 right;
		static const vector3 down;
		static const vector3 up;
		static const vector3 back;
		static const vector3 forward;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		vector3() = default;
		
		vector3(float x, float y, float z) : x(x), y(y), z(z) { }

		vector3(const glm::vec3& vector) : vector3(vector.x, vector.y, vector.z) { }

		static int get_length() { return 3; }

		static vector3 get_zero() { return zero; }
		static vector3 get_one() { return one; }
		static vector3 get_left() { return left; }
		static vector3 get_right() { return right; }
		static vector3 get_down() { return down; }
		static vector3 get_up() { return up; }
		static vector3 get_back() { return back; }
		static vector3 get_forward() { return forward; }

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
			return math::sqrt(x * x + y * y + z * z);
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

		float& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return (&x)[index];
		}

		float operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return (&x)[index];
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

		vector3& operator *= (float number) {
			x *= number;
			y *= number;
			z *= number;
			return *this;
		}

		vector3& operator /= (float number) {
			x /= number;
			y /= number;
			z /= number;
			return *this;
		}

		explicit operator vector2() const {
			return vector2(x, y);
		}

		operator glm::vec3() const {
			return glm::vec3(x, y, z);
		}
	};

	inline vector3 operator + (const vector3& vector) {
		return vector;
	}

	inline vector3 operator + (const vector3& left, const vector3& right) {
		return vector3(left) += right;
	}

	inline vector3 operator - (const vector3& vector) {
		return vector3(-vector.x, -vector.y, -vector.z);
	}

	inline vector3 operator - (const vector3& left, const vector3& right) {
		return vector3(left) -= right;
	}

	inline vector3 operator * (const vector3& vector, float number) {
		return vector3(vector) *= number;
	}

	inline vector3 operator / (const vector3& vector, float number) {
		return vector3(vector) /= number;
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