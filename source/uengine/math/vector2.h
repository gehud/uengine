#pragma once

#include "uengine/math/vector.h"
#include "uengine/core/assertion.h"

#include <ostream>

namespace ue {
	template<typename T>
	struct vector<2, T> {
	public:
		T x, y;

		constexpr vector() : x(0), y(0) { }

		constexpr vector(T x, T y) : x(x), y(y) { }

		constexpr vector(T scalar) : x(scalar), y(scalar) { }

		constexpr vector(const vector<2, T>& other) : x(other.x), y(other.y) { }

		static constexpr int length() { return 2; }

		static constexpr vector<2, T> one() { return vector<2, T>(1, 1); }

		static constexpr vector<2, T> zero() { return vector<2, T>(0, 0); }

		static constexpr vector<2, T> right() { return vector<2, T>(1, 0); }

		static constexpr vector<2, T> left() { return vector<2, T>(-1, 0); }

		static constexpr vector<2, T> up() { return vector<2, T>(0, 1); }

		static constexpr vector<2, T> down() { return vector<2, T>(0, -1); }

		constexpr T& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr T operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr vector<2, T>& operator += (T scalar) {
			this->x += scalar;
			this->y += scalar;
			return *this;
		}

		constexpr vector<2, T>& operator += (const vector<2, T>& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		constexpr vector<2, T>& operator -= (T scalar) {
			this->x -= scalar;
			this->y -= scalar;
			return *this;
		}

		constexpr vector<2, T>& operator -= (const vector<2, T>& other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		constexpr vector<2, T>& operator *= (T scalar) {
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}

		constexpr vector<2, T>& operator *= (const vector<2, T>& other) {
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}

		constexpr vector<2, T>& operator /= (T scalar) {
			this->x /= scalar;
			this->y /= scalar;
			return *this;
		}

		constexpr vector<2, T>& operator /= (const vector<2, T>& other) {
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		}
	};

	template<>
	struct vector<2, int> {
	public:
		int x, y;

		constexpr vector() : x(0), y(0) { }

		constexpr vector(int x, int y) : x(x), y(y) { }

		constexpr vector(int scalar) : x(scalar), y(scalar) { }

		constexpr vector(const vector<2, int>& other) : x(other.x), y(other.y) { }

		static constexpr int length() { return 2; }

		static constexpr vector<2, int> one() { return vector<2, int>(1, 1); }

		static constexpr vector<2, int> zero() { return vector<2, int>(0, 0); }

		static constexpr vector<2, int> right() { return vector<2, int>(1, 0); }

		static constexpr vector<2, int> left() { return vector<2, int>(-1, 0); }

		static constexpr vector<2, int> up() { return vector<2, int>(0, 1); }

		static constexpr vector<2, int> down() { return vector<2, int>(0, -1); }

		constexpr int& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr int operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr vector<2, int>& operator += (int scalar) {
			this->x += scalar;
			this->y += scalar;
			return *this;
		}

		constexpr vector<2, int>& operator += (const vector<2, int>& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		constexpr vector<2, int>& operator -= (int scalar) {
			this->x -= scalar;
			this->y -= scalar;
			return *this;
		}

		constexpr vector<2, int>& operator -= (const vector<2, int>& other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		constexpr vector<2, int>& operator *= (int scalar) {
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}

		constexpr vector<2, int>& operator *= (const vector<2, int>& other) {
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}

		constexpr vector<2, int>& operator /= (int scalar) {
			this->x /= scalar;
			this->y /= scalar;
			return *this;
		}

		constexpr vector<2, int>& operator /= (const vector<2, int>& other) {
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		}

		constexpr vector<2, int>& operator ++ () {
			++this->x;
			++this->y;
			return *this;
		}

		constexpr vector<2, int> operator ++ (int) {
			vector<2, int> result(*this);
			++(*this);
			return result;
		}

		constexpr vector<2, int>& operator -- () {
			--this->x;
			--this->y;
			return *this;
		}

		constexpr vector<2, int> operator -- (int) {
			vector<2, int> result(*this);
			--(*this);
			return result;
		}
	};

	template<typename T>
	constexpr vector<2, T> operator + (const vector<2, T>& v, T s) {
		return vector<2, T>(v.x + s, v.y + s);
	}

	template<typename T>
	constexpr vector<2, T> operator + (const vector<2, T>& l, const vector<2, T>& r) {
		return vector<2, T>(l.x + r.x, l.y + r.y);
	}

	template<typename T>
	constexpr vector<2, T> operator - (const vector<2, T>& v) {
		return vector<2, T>(-v.x, -v.y);
	}

	template<typename T>
	constexpr vector<2, T> operator - (const vector<2, T>& v, T s) {
		return vector<2, T>(v.x - s, v.y - s);
	}

	template<typename T>
	constexpr vector<2, T> operator - (const vector<2, T>& l, const vector<2, T>& r) {
		return vector<2, T>(l.x - r.x, l.y - r.y);
	}

	template<typename T>
	constexpr vector<2, T> operator * (const vector<2, T>& v, T s) {
		return vector<2, T>(v.x * s, v.y * s);
	}

	template<typename T>
	constexpr vector<2, T> operator * (const vector<2, T>& l, const vector<2, T>& r) {
		return vector<2, T>(l.x * r.x, l.y * r.y);
	}

	template<typename T>
	constexpr vector<2, T> operator / (const vector<2, T>& v, T s) {
		return vector<2, T>(v.x / s, v.y / s);
	}

	template<typename T>
	constexpr vector<2, T> operator / (const vector<2, T>& l, const vector<2, T>& r) {
		return vector<2, T>(l.x / r.x, l.y / r.y);
	}

	template<typename T>
	constexpr std::ostream& operator << (std::ostream& ostream, const vector<2, T>& v) {
		return ostream << "(" << v.x << ", " << v.y << ")";
	}

	template<typename T>
	using vector2 = vector<2, T>;

	typedef vector2<int> vector2i;
	typedef vector2<float> vector2f;
}