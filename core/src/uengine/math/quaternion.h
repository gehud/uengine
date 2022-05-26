#pragma once

#include "vector3.h"
#include "uengine/core/assertion.h"

#include <glm/gtc/quaternion.hpp>

namespace ue 
{
	struct quaternion 
	{
		static const quaternion identity;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		quaternion(float x, float y, float z, float w) 
			: x(x), y(y), z(z), w(w) { }

		quaternion(const glm::quat& quaternion) 
			: x(quaternion.x), y(quaternion.y), z(quaternion.z), w(quaternion.w) { }

		static quaternion euler_angles(const vector3& vector) 
		{
			return glm::quat(glm::radians((glm::vec3)vector));
		}

		vector3 get_euler_angles() const 
		{
			return glm::eulerAngles((glm::quat)*this);
		}

		void set_euler_angles(const vector3& value) 
		{
			*this = euler_angles(value);
		}

		operator glm::quat() const { return glm::quat(w, x, y, z); }

		float operator [] (int index) const 
		{
			UE_CORE_ASSERT(index > -1 && index < 4, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			}
		}

		quaternion operator * (const quaternion& other) const noexcept
		{
			return glm::quat(glm::mat4((glm::quat)*this) * glm::mat4((glm::quat)other));
		}

		quaternion& operator *= (const quaternion& other) noexcept
		{
			*this = glm::quat(glm::mat4((glm::quat)*this) * glm::mat4((glm::quat)other));
			return *this;
		}
	};
}