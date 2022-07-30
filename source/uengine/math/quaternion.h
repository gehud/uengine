#pragma once

#include "uengine/math/vector4.h"
#include "uengine/core/assertion.h"

#include <ostream>

namespace ue {
	struct quaternion {
	public:
		float x, y, z, w;

		constexpr quaternion() : x(0), y(0), z(0), w(1) { }

		constexpr quaternion(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) { }

		constexpr quaternion(const vector4f& vector)
			: quaternion(vector.x, vector.y, vector.z, vector.w) { }

		static constexpr quaternion identity() { return quaternion(0, 0, 0, 1); }

		static constexpr int length() { return 4; }

		static quaternion euler(const vector3f& vector) {
			quaternion result;

			vector3f radians = vector3f::radians(vector) * 0.5f;
			vector3f c = vector3f::cos(radians);
			vector3f s = vector3f::sin(radians);

			result.x = s.x * c.y * c.z - c.x * s.y * s.z;
			result.y = c.x * s.y * c.z + s.x * c.y * s.z;
			result.z = c.x * c.y * s.z - s.x * s.y * c.z;
			result.w = c.x * c.y * c.z + s.x * s.y * s.z;

			return result;
		}

		constexpr float& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out of range.");
			return (&x)[index];
		}

		constexpr float operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out of range.");
			return (&x)[index];
		}

		constexpr quaternion& operator *= (const quaternion& other) {
			quaternion l(*this);
			quaternion r(other);

			this->x = l.w * r.x + l.x * r.w + l.y * r.z - l.z * r.y;
			this->y = l.w * r.y + l.y * r.w + l.z * r.x - l.x * r.z;
			this->z = l.w * r.z + l.z * r.w + l.x * r.y - l.y * r.x;
			this->w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;

			return *this;
		}
	};

	inline quaternion operator * (const quaternion& l, const quaternion& r) {
		quaternion result;
		result.x = l.w * r.x + l.x * r.w + l.y * r.z - l.z * r.y;
		result.y = l.w * r.y + l.y * r.w + l.z * r.x - l.x * r.z;
		result.z = l.w * r.z + l.z * r.w + l.x * r.y - l.y * r.x;
		result.w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;
		return result;
	}

	inline bool operator == (const quaternion& left, const quaternion& right) {
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}

	inline bool operator != (const quaternion& left, const quaternion& right) {
		return !(left == right);
	}

	inline std::ostream& operator << (std::ostream& ostream, const quaternion& quaternion) {
		return ostream << "(" << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << ", " << quaternion.w << ")";
	}
}