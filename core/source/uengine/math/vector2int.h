#pragma once

#include "math.h"
#include "uengine/core/types.h"
#include "uengine/core/assertion.h"

#include <ostream>

namespace ue {
	struct vector2int {
		static const vector2int zero;
		static const vector2int one;
		static const vector2int right;
		static const vector2int left;
		static const vector2int up;
		static const vector2int down;

		int32 x = 0;
		int32 y = 0;

		vector2int(int32 x, int32 y) : x(x), y(y) { }

		static vector2int get_one() { return one; }
		static vector2int get_zero() { return zero; }
		static vector2int get_right() { return right; }
		static vector2int get_left() { return left; }
		static vector2int get_up() { return up; }
		static vector2int get_down() { return down; }

		float get_magnitude() const {
			return math::sqrt(x * x + y * y);
		}

		int32 operator [] (int32 index) const {
			UE_CORE_ASSERT(index <= 1, "Index out of range.");
			switch (index) {
				case 0: return x;
				case 1: return y;
			}
		}

		int32& operator [] (int32 index) {
			UE_CORE_ASSERT(index <= 1, "Index out of range.");
			switch (index) {
				case 0: return x;
				case 1: return y;
			}
		}

		vector2int& operator += (const vector2int& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		vector2int& operator -= (const vector2int& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}
	};

	inline vector2int operator + (const vector2int& vector) {
		return vector;
	}

	inline vector2int operator + (const vector2int& left, const vector2int& right) {
		return vector2int(left.x + right.x, left.y + right.y);
	}

	inline vector2int operator - (const vector2int& vector) {
		return vector2int(-vector.x, -vector.y);
	}

	inline vector2int operator - (const vector2int& left, const vector2int& right) {
		return vector2int(left.x - right.x, left.y - right.y);
	}

	inline vector2int operator * (const vector2int& vector, int32 number) {
		return vector2int(vector.x * number, vector.y * number);
	}

	inline vector2int operator / (const vector2int& vector, int32 number) {
		return vector2int(vector.x / number, vector.y / number);
	}

	inline bool operator == (const vector2int& left, const vector2int& right) {
		return left.x == right.x && left.y == right.y;
	}

	inline bool operator != (const vector2int& left, const vector2int& right) {
		return !(left == right);
	}

	inline std::ostream& operator << (std::ostream& ostream, const vector2int& vector) {
		return ostream << "(" << vector.x << ", " << vector.y << ")";
	}
}