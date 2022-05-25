#pragma once

#include "uengine/assertion.h"

#include <glm/glm.hpp>

namespace ue
{
	struct vector3
	{
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

		vector3(float x, float y, float z) : x(x), y(y), z(z) { }

		vector3(const glm::vec3 vector) : x(vector.x), y(vector.y), z(vector.z) { }

		float get_magnitude() const
		{
			return glm::length((glm::vec3)*this);
		}

		vector3 get_normalized() const
		{
			return glm::normalize((glm::vec3)*this);
		}

		void normalize()
		{
			*this = get_normalized();
		}

		operator glm::vec3() const noexcept { return glm::vec3(x, y, z); }

		float operator [] (int index) const
		{
			UE_CORE_ASSERT(index > -1 && index < 3, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			}
		}

		float& operator [] (int index)
		{
			UE_CORE_ASSERT(index > -1 && index < 3, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			}
		}

		vector3 operator + (const vector3& other) noexcept
		{
			return vector3(x + other.x, y + other.y, z + other.z);
		}

		vector3 operator - (const vector3& other) noexcept
		{
			return vector3(x - other.x, y - other.y, z - other.z);
		}

		vector3 operator * (float value) noexcept
		{
			return vector3(x * value, y * value, z * value);
		}

		vector3 operator / (float value)
		{
			return vector3(x / value, y / value, z / value);
		}
	};
}