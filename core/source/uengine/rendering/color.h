#pragma once

#include "uengine/math/vector4.h"

namespace ue 
{
	struct color 
	{
		static const color white;
		static const color black;
		static const color clear;
		static const color red;
		static const color green;
		static const color blue;

		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 0.0f;

		color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }
		color(const vector4& vector) : r(vector.x), g(vector.y), b(vector.z), a(vector.w) { }

		static color get_white() { return white; }
		static color get_black() { return black; }
		static color get_clear() { return clear; }
		static color get_red() { return red; }
		static color get_green() { return green; }
		static color get_blue() { return blue; }

		operator vector4() const { return vector4(r, g, b, a); }

		float operator [] (int index) const 
		{
			UE_CORE_ASSERT(index >= 0 && index <= 3, "Index out of range.");
			switch (index)
			{
			case 0: return r;
			case 1: return g;
			case 2: return b;
			case 3: return a;
			}
		}

		float& operator [] (int index)
		{
			UE_CORE_ASSERT(index >= 0 && index <= 3, "Index out of range.");
			switch (index)
			{
			case 0: return r;
			case 1: return g;
			case 2: return b;
			case 3: return a;
			}
		}

		color& operator += (const color& other)
		{
			r += other.r;
			g += other.g;
			b += other.b;
			a += other.a;
			return *this;
		}

		color& operator -= (const color& other)
		{
			r -= other.r;
			g -= other.g;
			b -= other.b;
			a -= other.a;
			return *this;
		}

		color& operator *= (const color& other)
		{
			r *= other.r;
			g *= other.g;
			b *= other.b;
			a *= other.a;
			return *this;
		}

		color& operator /= (const color& other)
		{
			r /= other.r;
			g /= other.g;
			b /= other.b;
			a /= other.a;
			return *this;
		}
	};

	inline color operator + (const color& left, const color& right)
	{
		return color(left.r + right.r, left.g + right.g, left.b + right.b, left.a + right.a);
	}

	inline color operator - (const color& left, const color& right)
	{
		return color(left.r - right.r, left.g - right.g, left.b - right.b, left.a - right.a);
	}

	inline color operator - (const color& vector)
	{
		return color(-vector.r, -vector.g, -vector.b, -vector.a);
	}

	inline color operator * (const color& left, const color& right)
	{
		return color(left.r * right.r, left.g * right.g, left.b * right.b, left.a * right.a);
	}

	inline color operator * (const color& vector, float number)
	{
		return color(vector.r * number, vector.g * number, vector.b * number, vector.a * number);
	}

	inline color operator / (const color& left, const color& right)
	{
		return color(left.r / right.r, left.g / right.g, left.b / right.b, left.a / right.a);
	}

	inline color operator / (const color& vector, float number)
	{
		return color(vector.r / number, vector.g / number, vector.b / number, vector.a / number);
	}

	inline bool operator == (const color& left, const color& right)
	{
		return left.r == right.r && left.g == right.g && left.b == right.b && left.a == right.a;
	}

	inline bool operator != (const color& left, const color& right)
	{
		return !(left == right);
	}

	inline std::ostream& operator << (std::ostream& ostream, const color& vector)
	{
		return ostream << "(" << vector.r << ", " << vector.g << ", " << vector.b << ", " << vector.a << ")";
	}
}