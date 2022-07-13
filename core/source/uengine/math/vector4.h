#pragma once

#include "uengine/core/types.h"
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

		static vector4 get_zero() { return zero; }
		static vector4 get_one() { return one; }

		static float dot(const vector4& a, const vector4& b) {
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		}

		float get_magnitude() const {
			return std::sqrtf(x * x + y * y + z * z + w * w);
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

		float operator [] (uint32 index) const {
			UE_CORE_ASSERT(index <= 3, "Index out of range.");
			switch (index) {
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;
			}
		}

		float& operator [] (uint32 index) {
			UE_CORE_ASSERT(index <= 3, "Index out of range.");
			switch (index) {
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;
			}
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
	};

	inline vector4 operator + (const vector4& vector) {
		return vector;
	}

	inline vector4 operator + (const vector4& left, const vector4& right) {
		return vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}

	inline vector4 operator - (const vector4& vector) {
		return vector4(-vector.x, -vector.y, -vector.z, -vector.w);
	}

	inline vector4 operator - (const vector4& left, const vector4& right) {
		return vector4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}

	inline vector4 operator * (const vector4& vector, float number) {
		return vector4(vector.x * number, vector.y * number, vector.z * number, vector.w * number);
	}

	inline vector4 operator / (const vector4& vector, float number) {
		return vector4(vector.x / number, vector.y / number, vector.z / number, vector.w / number);
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