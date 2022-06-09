#pragma once

#include "uengine/core/assertion.h"

namespace ue
{
	struct vector2_int
	{
		static const vector2_int one;
		static const vector2_int zero;
		static const vector2_int right;
		static const vector2_int left;
		static const vector2_int up;
		static const vector2_int down;

		int x = 0;
		int y = 0;

		vector2_int(int x, int y) : x(x), y(y) { }

		static vector2_int get_one() { return one; }
		static vector2_int get_zero() { return zero; }
		static vector2_int get_right() { return right; }
		static vector2_int get_left() { return left; }
		static vector2_int get_up() { return up; }
		static vector2_int get_down() { return down; }

		float get_magnitude() const
		{
			return std::sqrtf(static_cast<float>(x * x + y * y));
		}

		int operator [] (int index) const
		{
			UE_CORE_ASSERT(index >= 0 && index <= 1, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			}
		}

		int& operator [] (int index)
		{
			UE_CORE_ASSERT(index >= 0 && index <= 1, "Index out of range.");
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			}
		}

		vector2_int& operator += (const vector2_int& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		vector2_int& operator -= (const vector2_int& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		vector2_int& operator *= (const vector2_int& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		vector2_int& operator /= (const vector2_int& other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
	};

	inline vector2_int operator + (const vector2_int& left, const vector2_int& right)
	{
		return vector2_int(left.x + right.x, left.y + right.y);
	}

	inline vector2_int operator + (const vector2_int& vector)
	{
		return vector2_int(vector.x, vector.y);
	}

	inline vector2_int operator - (const vector2_int& left, const vector2_int& right)
	{
		return vector2_int(left.x - right.x, left.y - right.y);
	}

	inline vector2_int operator - (const vector2_int& vector)
	{
		return vector2_int(-vector.x, -vector.y);
	}

	inline vector2_int operator * (const vector2_int& left, const vector2_int& right)
	{
		return vector2_int(left.x * right.x, left.y * right.y);
	}

	inline vector2_int operator * (const vector2_int& vector, int number)
	{
		return vector2_int(vector.x * number, vector.y * number);
	}

	inline vector2_int operator / (const vector2_int& left, const vector2_int& right)
	{
		return vector2_int(left.x / right.x, left.y / right.y);
	}

	inline vector2_int operator / (const vector2_int& vector, int number)
	{
		return vector2_int(vector.x / number, vector.y / number);
	}

	inline bool operator > (const vector2_int& left, const vector2_int& right)
	{
		return left.x > right.x && left.y > right.y;
	}

	inline bool operator >= (const vector2_int& left, const vector2_int& right)
	{
		return left.x >= right.x && left.y >= right.y;
	}

	inline bool operator < (const vector2_int& left, const vector2_int& right)
	{
		return left.x < right.x&& left.y < right.y;
	}

	inline bool operator <= (const vector2_int& left, const vector2_int& right)
	{
		return left.x <= right.x && left.y <= right.y;
	}

	inline bool operator == (const vector2_int& left, const vector2_int& right)
	{
		return left.x == right.x && left.y == right.y;
	}

	inline bool operator != (const vector2_int& left, const vector2_int& right)
	{
		return !(left == right);
	}

	inline std::ostream& operator << (std::ostream& ostream, const vector2_int& vector)
	{
		return ostream << "(" << vector.x << ", " << vector.y << ")";
	}
}