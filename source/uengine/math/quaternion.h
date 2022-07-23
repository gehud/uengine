#pragma once

#include "uengine/math/vector3.h"
#include "uengine/math/vector4.h"
#include "uengine/core/assertion.h"

#include <glm/gtx/quaternion.hpp>

#include <ostream>

namespace ue {
	struct quaternion {
	public:
		static const quaternion identity;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		quaternion() {
			*this = identity;
		}

		quaternion(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) { }

		quaternion(const vector4& vector) 
			: quaternion(vector.x, vector.y, vector.z, vector.w) { }

		quaternion(const glm::quat& quaternion) 
			: quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w) { }

		static int get_length() { return 4; }

		static quaternion euler(const vector3& vector) {
			return glm::quat(static_cast<glm::vec3>(vector));
		}

		static quaternion euler(float x, float y, float z) {
			return euler(vector3(x, y, z));
		}

		vector3 get_euler_angles() const {
			return glm::eulerAngles(static_cast<glm::quat>(*this));
		}

		float& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return (&x)[index];
		}

		float operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return (&x)[index];
		}

		quaternion& operator *= (const quaternion& other) {
			return *this = (static_cast<glm::quat>(*this) * static_cast<glm::quat>(other));
		}

		operator glm::quat() const {
			return glm::quat(w, x, y, z);
		}
	};

	inline quaternion operator * (const quaternion& left, const quaternion& right) {
		return quaternion(left) *= right;
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