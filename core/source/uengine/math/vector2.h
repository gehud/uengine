#pragma once

#include "uengine/core/assertion.h"

#include <glm/vec2.hpp>

namespace ue 
{
	struct vector2 
	{
		static const vector2 one;
		static const vector2 zero;
		static const vector2 right;
		static const vector2 left;
		static const vector2 up;
		static const vector2 down;

		float x = 0.0f;
		float y = 0.0f;

		vector2(float x, float y) : x(x), y(y) { }

		vector2(const glm::vec2 vector) : x(vector.x), y(vector.y) { }

		static vector2 get_one() { return one; }
		static vector2 get_zero() { return zero; }
		static vector2 get_right() { return right; }
		static vector2 get_left() { return left; }
		static vector2 get_up() { return up; }
		static vector2 get_down() { return down; }

		float get_magnitude() const
		{
			return std::sqrtf(x * x + y * y);
		}

		vector2 get_normalized() const 
		{
			float magnitude = get_magnitude();
			if (magnitude > 0)
				return vector2(x / magnitude, y / magnitude);
			return zero;
		}

		void normalize() 
		{
			*this = get_normalized();
		}

		operator glm::vec2() const { return glm::vec2(x, y); }

		float operator [] (int index) const
		{
			UE_CORE_ASSERT(index >= 0 && index <= 1, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			}
		}

		float& operator [] (int index)
		{
			UE_CORE_ASSERT(index >= 0 && index <= 1, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			}
		}

		vector2& operator += (const vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		vector2& operator -= (const vector2& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		vector2& operator *= (const vector2& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		vector2& operator /= (const vector2& other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
	};

	inline vector2 operator + (const vector2& left, const vector2& right)
	{
		return vector2(left.x + right.x, left.y + right.y);
	}

	inline vector2 operator + (const vector2& vector)
	{
		return vector2(vector.x, vector.y);
	}

	inline vector2 operator - (const vector2& left, const vector2& right)
	{
		return vector2(left.x - right.x, left.y - right.y);
	}

	inline vector2 operator - (const vector2& vector)
	{
		return vector2(-vector.x, -vector.y);
	}

	inline vector2 operator * (const vector2& left, const vector2& right)
	{
		return vector2(left.x * right.x, left.y * right.y);
	}

	inline vector2 operator * (const vector2& vector, float number)
	{
		return vector2(vector.x * number, vector.y * number);
	}

	inline vector2 operator / (const vector2& left, const vector2& right)
	{
		return vector2(left.x / right.x, left.y / right.y);
	}

	inline vector2 operator / (const vector2& vector, float number)
	{
		return vector2(vector.x / number, vector.y / number);
	}

	inline bool operator > (const vector2& left, const vector2& right) 
	{
		return left.x > right.x && left.y > right.y;
	}

	inline bool operator >= (const vector2& left, const vector2& right)
	{
		return left.x >= right.x && left.y >= right.y;
	}

	inline bool operator < (const vector2& left, const vector2& right)
	{
		return left.x < right.x && left.y < right.y;
	}

	inline bool operator <= (const vector2& left, const vector2& right)
	{
		return left.x <= right.x && left.y <= right.y;
	}

	inline bool operator == (const vector2& left, const vector2& right)
	{
		return left.x == right.x && left.y == right.y;
	}

	inline bool operator != (const vector2& left, const vector2& right)
	{
		return !(left == right);
	}

	inline std::ostream& operator << (std::ostream& ostream, const vector2& vector)
	{
		return ostream << "(" << vector.x << ", " << vector.y << ")";
	}
}