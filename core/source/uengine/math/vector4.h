#pragma once

#include "uengine/math/math.h"
#include "uengine/core/assertion.h"

#include <ostream>

namespace ue {
	struct vector4 {
		static const vector4 zero;
		static const vector4 one;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		vector4() = default;

		vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

		static int get_length() { return 4; }

		static vector4 get_zero() { return zero; }
		static vector4 get_one() { return one; }

		static float dot(const vector4& a, const vector4& b) {
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		}

		float get_magnitude() const {
			return math::sqrt(x * x + y * y + z * z + w * w);
		}

		vector4 get_normalized() const {
			float magnitude = get_magnitude();
			if (magnitude > 0)
				return vector4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
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

		vector4& operator += (const vector4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		vector4& operator -= (const vector4& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		vector4& operator *= (float number) {
			x *= number;
			y *= number;
			z *= number;
			w *= number;
			return *this;
		}

		vector4& operator /= (float number) {
			x /= number;
			y /= number;
			z /= number;
			w /= number;
			return *this;
		}
	};

	inline vector4 operator + (const vector4& vector) {
		return vector;
	}

	inline vector4 operator + (const vector4& left, const vector4& right) {
		return vector4(left) += right;
	}

	inline vector4 operator - (const vector4& vector) {
		return vector4(-vector.x, -vector.y, -vector.z, -vector.w);
	}

	inline vector4 operator - (const vector4& left, const vector4& right) {
		return vector4(left) -= right;
	}

	inline vector4 operator * (const vector4& vector, float number) {
		return vector4(vector) *= number;
	}

	inline vector4 operator / (const vector4& vector, float number) {
		return vector4(vector) /= number;
	}

	inline bool operator == (const vector4& left, const vector4& right) {
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}

	inline bool operator != (const vector4& left, const vector4& right) {
		return !(left == right);
	}

	inline std::ostream& operator << (std::ostream& ostream, const vector4& vector) {
		return ostream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
	}
}