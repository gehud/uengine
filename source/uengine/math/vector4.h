#pragma once

#include "uengine/math/vector.h"
#include "uengine/core/assertion.h"

#include <ostream>

namespace ue {
	template<typename T>
	struct vector<4, T> {
	public:
		T x, y, z, w;

		constexpr vector() : x(0), y(0), z(0), w(0) { }

		constexpr vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }

		constexpr vector(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }

		constexpr vector(const vector<4, T>& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }

		static constexpr int length() { return 4; }

		static constexpr vector<4, T> one() { return vector<4, T>(1, 1, 1, 1); }
								
		static constexpr vector<4, T> zero() { return vector<4, T>(0, 0, 0, 0); }

		static constexpr float dot(const vector<4, T>& left, const vector<4, T>& right) {
			return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);
		}

		constexpr T& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr T operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr vector<4, T>& operator += (T scalar) {
			this->x += scalar;
			this->y += scalar;
			this->z += scalar;
			this->w += scalar;
			return *this;
		}

		constexpr vector<4, T>& operator += (const vector<4, T>& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}

		constexpr vector<4, T>& operator -= (T scalar) {
			this->x -= scalar;
			this->y -= scalar;
			this->z -= scalar;
			this->w -= scalar;
			return *this;
		}

		constexpr vector<4, T>& operator -= (const vector<4, T>& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this;
		}

		constexpr vector<4, T>& operator *= (T scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			this->w *= scalar;
			return *this;
		}

		constexpr vector<4, T>& operator *= (const vector<4, T>& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;
			return *this;
		}

		constexpr vector<4, T>& operator /= (T scalar) {
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			this->w /= scalar;
			return *this;
		}

		constexpr vector<4, T>& operator /= (const vector<4, T>& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;
			return *this;
		}
	};

	template<>
	struct vector<4, int> {
	public:
		int x, y, z, w;

		constexpr vector() : x(0), y(0), z(0), w(0) { }

		constexpr vector(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) { }

		constexpr vector(int scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }

		constexpr vector(const vector<4, int>& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }

		static constexpr int length() { return 4; }

		static constexpr vector<4, int> one() { return vector<4, int>(1, 1, 1, 1); }

		static constexpr vector<4, int> zero() { return vector<4, int>(0, 0, 0, 0); }

		constexpr int& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr int operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr vector<4, int>& operator += (int scalar) {
			this->x += scalar;
			this->y += scalar;
			this->z += scalar;
			this->w += scalar;
			return *this;
		}

		constexpr vector<4, int>& operator += (const vector<4, int>& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}

		constexpr vector<4, int>& operator -= (int scalar) {
			this->x -= scalar;
			this->y -= scalar;
			this->z -= scalar;
			this->w -= scalar;
			return *this;
		}

		constexpr vector<4, int>& operator -= (const vector<4, int>& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this;
		}

		constexpr vector<4, int>& operator *= (int scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			this->w *= scalar;
			return *this;
		}

		constexpr vector<4, int>& operator *= (const vector<4, int>& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;
			return *this;
		}

		constexpr vector<4, int>& operator /= (int scalar) {
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			this->w /= scalar;
			return *this;
		}

		constexpr vector<4, int>& operator /= (const vector<4, int>& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;
			return *this;
		}

		constexpr vector<4, int>& operator ++ () {
			++this->x;
			++this->y;
			++this->z;
			++this->w;
			return *this;
		}

		constexpr vector<4, int> operator ++ (int) {
			vector<4, int> result(*this);
			++(*this);
			return result;
		}

		constexpr vector<4, int>& operator -- () {
			--this->x;
			--this->y;
			--this->z;
			--this->w;
			return *this;
		}

		constexpr vector<4, int> operator -- (int) {
			vector<4, int> result(*this);
			--(*this);
			return result;
		}
	};

	template<typename T>
	constexpr vector<4, T> operator + (const vector<4, T>& v, T s) {
		return vector<4, T>(v.x + s, v.y + s, v.z + s, v.w + s);
	}

	template<typename T>
	constexpr vector<4, T> operator + (const vector<4, T>& l, const vector<4, T>& r) {
		return vector<4, T>(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
	}

	template<typename T>
	constexpr vector<4, T> operator - (const vector<4, T>& v) {
		return vector<4, T>(-v.x, -v.y, -v.z, -v.w);
	}

	template<typename T>
	constexpr vector<4, T> operator - (const vector<4, T>& v, T s) {
		return vector<4, T>(v.x - s, v.y - s, v.z - s, v.w - s);
	}

	template<typename T>
	constexpr vector<4, T> operator - (const vector<4, T>& l, const vector<4, T>& r) {
		return vector<4, T>(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
	}

	template<typename T>
	constexpr vector<4, T> operator * (const vector<4, T>& v, T s) {
		return vector<4, T>(v.x * s, v.y * s, v.z * s, v.w * s);
	}

	template<typename T>
	constexpr vector<4, T> operator * (const vector<4, T>& l, const vector<4, T>& r) {
		return vector<4, T>(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
	}

	template<typename T>
	constexpr vector<4, T> operator / (const vector<4, T>& v, T s) {
		return vector<4, T>(v.x / s, v.y / s, v.z / s, v.w / s);
	}

	template<typename T>
	constexpr vector<4, T> operator / (const vector<4, T>& l, const vector<4, T>& r) {
		return vector<4, T>(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
	}

	template<typename T>
	constexpr std::ostream& operator << (std::ostream& ostream, const vector<4, T>& v) {
		return ostream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	}

	template<typename T>
	using vector4 = vector<4, T>;

	typedef vector4<int> vector4i;
	typedef vector4<float> vector4f;
}