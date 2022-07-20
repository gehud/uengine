#pragma once

#include "uengine/math/vector3.h"
#include "uengine/math/matrix4x4.h"
#include "uengine/core/assertion.h"

namespace ue {
	struct quaternion {
	public:
		float x, y, z, w;

		quaternion(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) { }

		quaternion(const vector3& euler) {
			auto c = vector3::cos(euler * 0.5f);
			auto s = vector3::sin(euler * 0.5f);

			x = s.x * c.y * c.z - c.x * s.y * s.z;
			y = c.x * s.y * c.z + s.x * c.y * s.z;
			z = c.x * c.y * s.z - s.x * s.y * c.z;
			w = c.x * c.y * c.z + s.x * s.y * s.z;
		}

		static int get_length() {
			return 4;
		}

		float& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return (&x)[index];
		}

		float operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return (&x)[index];
		}

		operator matrix4x4() const {
			matrix4x4 result(matrix4x4::identity);

			float qxx = x * x;
			float qyy = y * y;
			float qzz = z * z;
			float qxz = x * z;
			float qxy = x * y;
			float qyz = y * z;
			float qwx = w * x;
			float qwy = w * y;
			float qwz = w * z;

			result[0][0] = 1.0f - 2.0f * (qyy + qzz);
			result[0][1] = 2.0f * (qxy + qwz);
			result[0][2] = 2.0f * (qxz - qwy);

			result[1][0] = 2.0f * (qxy - qwz);
			result[1][1] = 1.0f - 2.0f * (qxx + qzz);
			result[1][2] = 2.0f * (qyz + qwx);

			result[2][0] = 2.0f * (qxz + qwy);
			result[2][1] = 2.0f * (qyz - qwx);
			result[2][2] = 1.0f - 2.0f * (qxx + qyy);

			return result;
		}

		quaternion& operator += (const quaternion& other) {
			this->x += other.x;
			this->y += other.x;
			this->z += other.x;
			this->w += other.x;
			return *this;
		}

		quaternion& operator -= (const quaternion& other) {
			x -= other.x;
			y -= other.x;
			z -= other.x;
			w -= other.x;
			return *this;
		}

		quaternion& operator *= (const quaternion& other) {
			x = w * other.x + x * other.w + y * other.z - z * other.y;
			y = w * other.y + y * other.w + z * other.x - x * other.z;
			z = w * other.z + z * other.w + x * other.y - y * other.x;
			w = w * other.w - x * other.x - y * other.y - z * other.z;
			return *this;
		}

		quaternion& operator *= (float number) {
			x *= number;
			y *= number; 
			z *= number; 
			w *= number; 
			return *this;
		}

		quaternion& operator /= (float number) {
			x /= number;
			y /= number;
			z /= number;
			w /= number;
			return *this;
		}
	};
}

inline ue::quaternion operator + (const ue::quaternion& quaternion) {
	return quaternion;
}

inline ue::quaternion operator + (const ue::quaternion& left, const ue::quaternion& right) {
	return ue::quaternion(left) *= right;
}

inline ue::quaternion operator - (const ue::quaternion& quaternion) {
	return ue::quaternion(-quaternion.x, -quaternion.y, -quaternion.z, -quaternion.w);
}

inline ue::quaternion operator - (const ue::quaternion& left, const ue::quaternion& right) {
	return ue::quaternion(left) *= right;
}

inline ue::quaternion operator * (const ue::quaternion& left, const ue::quaternion& right) {
	return ue::quaternion(left) *= right;
}

inline ue::quaternion operator * (const ue::quaternion& quaternion, float number) {
	return ue::quaternion(quaternion) *= number;
}

inline ue::quaternion operator / (const ue::quaternion& quaternion, float number) {
	return ue::quaternion(quaternion) /= number;
}

inline bool operator == (const ue::quaternion& left, const ue::quaternion& right) {
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}

inline bool operator != (const ue::quaternion& left, const ue::quaternion& right) {
	return !(left == right);
}