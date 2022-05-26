#pragma once

#include "uengine/core/assertion.h"

#include <glm/glm.hpp>

#include <ostream>

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

		static vector3 get_one() { return one; }
		static vector3 get_zero() { return zero; }
		static vector3 get_right() { return right; }
		static vector3 get_left() { return left; }
		static vector3 get_up() { return up; }
		static vector3 get_down() { return down; }
		static vector3 get_forward() { return forward; }
		static vector3 get_back() { return back; }

		float get_magnitude() const
		{
			return std::sqrtf(x * x + y * y + z * z);
		}

		vector3 get_normalized() const
		{
			float magnitude = get_magnitude();
			if (magnitude > 0)
				return vector3(x / magnitude, y / magnitude, z / magnitude);
			return zero;
		}

		void normalize()
		{
			*this = get_normalized();
		}

		operator glm::vec3() const { return glm::vec3(x, y, z); }

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

		vector3& operator += (const vector3& other) 
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		vector3& operator -= (const vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		vector3& operator *= (const vector3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		vector3& operator /= (const vector3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
	};

	inline vector3 operator + (const vector3& left, const vector3& right)
	{
		return vector3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	inline vector3 operator - (const vector3& left, const vector3& right)
	{
		return vector3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	inline vector3 operator - (const vector3& vector)
	{
		return vector3(-vector.x, -vector.y, -vector.z);
	}

	inline vector3 operator * (const vector3& left, const vector3& right)
	{
		return vector3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	inline vector3 operator * (const vector3& vector, float number)
	{
		return vector3(vector.x * number, vector.y * number, vector.z * number);
	}

	inline vector3 operator / (const vector3& left, const vector3& right)
	{
		return vector3(left.x / right.x, left.y / right.y, left.z / right.z);
	}

	inline vector3 operator / (const vector3& vector, float number)
	{
		return vector3(vector.x / number, vector.y / number, vector.z / number);
	}

	inline bool operator == (const vector3& left, const vector3& right)
	{
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	inline bool operator != (const vector3& left, const vector3& right)
	{
		return !(left == right);
	}

	inline std::ostream& operator << (std::ostream& ostream, const vector3& vector) 
	{
		return ostream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	}
}