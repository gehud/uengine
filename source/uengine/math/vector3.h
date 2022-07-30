#pragma once

#include "uengine/math/math.h"
#include "uengine/math/vector.h"
#include "uengine/core/assertion.h"

#include <ostream>

namespace ue {
	template<typename T>
	struct vector<3, T> {
	public:
		T x, y, z;

		constexpr vector() : x(0), y(0), z(0) { }

		constexpr vector(T x, T y, T z) : x(x), y(y), z(z) { }

		constexpr vector(T scalar) : x(scalar), y(scalar), z(scalar) { }

		constexpr vector(const vector<3, T>& other) : x(other.x), y(other.y), z(other.z) { }

		static constexpr int length() { return 3; }

		static constexpr vector<3, T> one() { return vector<3, T>(1, 1, 1); }

		static constexpr vector<3, T> zero() { return vector<3, T>(0, 0, 0); }

		static constexpr vector<3, T> right() { return vector<3, T>(1, 0, 0); }

		static constexpr vector<3, T> left() { return vector<3, T>(-1, 0, 0); }

		static constexpr vector<3, T> up() { return vector<3, T>(0, 1, 0); }

		static constexpr vector<3, T> down() { return vector<3, T>(0, -1, 0); }

		static constexpr vector<3, T> forward() { return vector<3, T>(0, 0, 1); }

		static constexpr vector<3, T> back() { return vector<3, T>(0, 0, -1); }

		static constexpr vector<3, T> sin(const vector<3, T>& vector) {
			return ue::vector<3, T>(math::sin(vector.x), math::sin(vector.y), math::sin(vector.z));
		}

		static constexpr vector<3, T> cos(const vector<3, T>& vector) {
			return ue::vector<3, T>(math::cos(vector.x), math::cos(vector.y), math::cos(vector.z));
		}

		static constexpr vector<3, T> radians(const vector<3, T>& vector) {
			return ue::vector<3, T>(math::radians(vector.x), math::radians(vector.y), math::radians(vector.z));
		}

		static constexpr vector<3, T> degrees(const vector<3, T>& vector) {
			return ue::vector<3, T>(math::degrees(vector.x), math::degrees(vector.y), math::degrees(vector.z));
		}

		constexpr T& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr T operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr vector<3, T>& operator += (T scalar) {
			this->x += scalar;
			this->y += scalar;
			this->z += scalar;
			return *this;
		}

		constexpr vector<3, T>& operator += (const vector<3, T>& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		constexpr vector<3, T>& operator -= (T scalar) {
			this->x -= scalar;
			this->y -= scalar;
			this->z -= scalar;
			return *this;
		}

		constexpr vector<3, T>& operator -= (const vector<3, T>& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		constexpr vector<3, T>& operator *= (T scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			return *this;
		}

		constexpr vector<3, T>& operator *= (const vector<3, T>& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}

		constexpr vector<3, T>& operator /= (T scalar) {
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			return *this;
		}

		constexpr vector<3, T>& operator /= (const vector<3, T>& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			return *this;
		}
	};

	template<>
	struct vector<3, int> {
	public:
		int x, y, z;

		constexpr vector() : x(0), y(0), z(0) { }

		constexpr vector(int x, int y, int z) : x(x), y(y), z(z) { }

		constexpr vector(int scalar) : x(scalar), y(scalar), z(scalar) { }

		constexpr vector(const vector<3, int>& other) : x(other.x), y(other.y), z(other.z) { }

		static constexpr int length() { return 3; }

		static constexpr vector<3, int> one() { return vector<3, int>(1, 1, 1); }

		static constexpr vector<3, int> zero() { return vector<3, int>(0, 0, 0); }
								   
		static constexpr vector<3, int> right() { return vector<3, int>(1, 0, 0); }
								   
		static constexpr vector<3, int> left() { return vector<3, int>(-1, 0, 0); }
								   
		static constexpr vector<3, int> up() { return vector<3, int>(0, 1, 0); }
								   
		static constexpr vector<3, int> down() { return vector<3, int>(0, -1, 0); }
								   
		static constexpr vector<3, int> forward() { return vector<3, int>(0, 0, 1); }
								   
		static constexpr vector<3, int> back() { return vector<3, int>(0, 0, -1); }

		constexpr int& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr int operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out or range.");
			return (&x)[index];
		}

		constexpr vector<3, int>& operator += (int scalar) {
			this->x += scalar;
			this->y += scalar;
			this->z += scalar;
			return *this;
		}

		constexpr vector<3, int>& operator += (const vector<3, int>& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		constexpr vector<3, int>& operator -= (int scalar) {
			this->x -= scalar;
			this->y -= scalar;
			this->z -= scalar;
			return *this;
		}

		constexpr vector<3, int>& operator -= (const vector<3, int>& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		constexpr vector<3, int>& operator *= (int scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			return *this;
		}

		constexpr vector<3, int>& operator *= (const vector<3, int>& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}

		constexpr vector<3, int>& operator /= (int scalar) {
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			return *this;
		}

		constexpr vector<3, int>& operator /= (const vector<3, int>& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			return *this;
		}

		constexpr vector<3, int>& operator ++ () {
			++this->x;
			++this->y;
			++this->z;
			return *this;
		}

		constexpr vector<3, int> operator ++ (int) {
			vector<3, int> result(*this);
			++(*this);
			return result;
		}

		constexpr vector<3, int>& operator -- () {
			--this->x;
			--this->y;
			--this->z;
			return *this;
		}

		constexpr vector<3, int> operator -- (int) {
			vector<3, int> result(*this);
			--(*this);
			return result;
		}
	};

	template<typename T>
	constexpr vector<3, T> operator + (const vector<3, T>& v, T s) {
		return vector<3, T>(v.x + s, v.y + s, v.z + s);
	}

	template<typename T>
	constexpr vector<3, T> operator + (const vector<3, T>& l, const vector<3, T>& r) {
		return vector<3, T>(l.x + r.x, l.y + r.y, l.z + r.z);
	}

	template<typename T>
	constexpr vector<3, T> operator - (const vector<3, T>& v) {
		return vector<3, T>(-v.x, -v.y, -v.z);
	}

	template<typename T>
	constexpr vector<3, T> operator - (const vector<3, T>& v, T s) {
		return vector<3, T>(v.x - s, v.y - s, v.z - s);
	}

	template<typename T>
	constexpr vector<3, T> operator - (const vector<3, T>& l, const vector<3, T>& r) {
		return vector<3, T>(l.x - r.x, l.y - r.y, l.z - r.z);
	}

	template<typename T>
	constexpr vector<3, T> operator * (const vector<3, T>& v, T s) {
		return vector<3, T>(v.x * s, v.y * s, v.z * s);
	}

	template<typename T>
	constexpr vector<3, T> operator * (const vector<3, T>& l, const vector<3, T>& r) {
		return vector<3, T>(l.x * r.x, l.y * r.y, l.z * r.z);
	}

	template<typename T>
	constexpr vector<3, T> operator / (const vector<3, T>& v, T s) {
		return vector<3, T>(v.x / s, v.y / s, v.z / s);
	}

	template<typename T>
	constexpr vector<3, T> operator / (const vector<3, T>& l, const vector<3, T>& r) {
		return vector<3, T>(l.x / r.x, l.y / r.y, l.z / r.z);
	}

	template<typename T>
	constexpr std::ostream& operator << (std::ostream& ostream, const vector<3, T>& v) {
		return ostream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}

	template<typename T>
	using vector3 = vector<3, T>;

	typedef vector3<int> vector3i;
	typedef vector3<float> vector3f;
}