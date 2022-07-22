#pragma once

#include "uengine/math/vector3.h"
#include "uengine/math/vector4.h"
#include "uengine/core/assertion.h"

namespace ue {
	struct quaternion {
	public:
		static const quaternion identity;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		quaternion() = default;

		quaternion(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) { }

		quaternion(const vector4& vector) 
			: quaternion(vector.x, vector.y, vector.z, vector.w) { }

		static int get_length() { return 4; }

		static quaternion euler(float x, float y, float z) {
			vector3 vector(x, y, z);

			auto c = vector3::cos(vector * 0.5f);
			auto s = vector3::sin(vector * 0.5f);

			return quaternion(s.x * c.y * c.z - c.x * s.y * s.z,
							  c.x * s.y * c.z + s.x * c.y * s.z,
							  c.x * c.y * s.z - s.x * s.y * c.z,
							  c.x * c.y * c.z + s.x * s.y * s.z);
		}

		static quaternion euler(const vector3& vector) {
			return euler(vector.x, vector.y, vector.z);
		}

		float get_pitch() const {
			float y = 2.0f * (this->y * this->z + this->w * this->x);
			float x = this->w * this->w - this->x * this->x - this->y * this->y + this->z * this->z;

			if (x == 0 && y == 0)
				return 2.0f * math::atan2(this->x, this->w);

			return math::atan2(y, x);
		}

		float get_yaw() const {
			return math::asin(math::clamp(-2.0f * (x * z - w * y), -1.0f, 1.0f));
		}

		float get_roll() const {
			float y = 2.0f * (this->x * this->y + this->w * this->z);
			float x = this->w * this->w + this->x * this->x - this->y * this->y - this->z * this->z;

			if (x == 0 && y == 0)
				return 0.0f;

			return math::atan2(y, x);
		}

		vector3 get_euler_angles() const {
			return vector3(get_pitch(), get_yaw(), get_roll());
		}

		void set_euler_angles(const vector3& value) {
			auto c = vector3::cos(value * 0.5f);
			auto s = vector3::sin(value * 0.5f);

			x = s.x * c.y * c.z - c.x * s.y * s.z;
			y = c.x * s.y * c.z + s.x * c.y * s.z;
			z = c.x * c.y * s.z - s.x * s.y * c.z;
			w = c.x * c.y * c.z + s.x * s.y * s.z;
		}

		float& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return (&x)[index];
		}

		float operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return (&x)[index];
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

	inline quaternion operator + (const quaternion& quaternion) {
		return quaternion;
	}

	inline quaternion operator + (const quaternion& left, const quaternion& right) {
		return quaternion(left) *= right;
	}

	inline quaternion operator - (const quaternion& quaternion) {
		return ue::quaternion(-quaternion.x, -quaternion.y, -quaternion.z, -quaternion.w);
	}

	inline quaternion operator - (const quaternion& left, const quaternion& right) {
		return quaternion(left) *= right;
	}

	inline quaternion operator * (const quaternion& left, const quaternion& right) {
		return quaternion(left) *= right;
	}

	inline quaternion operator * (const quaternion& quaternion, float number) {
		return ue::quaternion(quaternion) *= number;
	}

	inline quaternion operator / (const quaternion& quaternion, float number) {
		return ue::quaternion(quaternion) /= number;
	}

	inline bool operator == (const quaternion& left, const quaternion& right) {
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}

	inline bool operator != (const quaternion& left, const quaternion& right) {
		return !(left == right);
	}
}