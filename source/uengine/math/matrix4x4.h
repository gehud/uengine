#pragma once

#include "uengine/math/vector4.h"
#include "uengine/math/vector3.h"

namespace ue {
	struct matrix4x4 {
	public:
		static const matrix4x4 identity;

		matrix4x4() = default;

		matrix4x4(float x0, float y0, float z0, float w0,
				  float x1, float y1, float z1, float w1,
				  float x2, float y2, float z2, float w2,
				  float x3, float y3, float z3, float w3) : _values { { x0, y0, z0, w0 },
																	  { x1, y1, z1, w1 },
																	  { x2, y2, z2, w2 },
																	  { x3, y3, z3, w3 } } { }

		static int get_length() { return 4; }

		static matrix4x4 get_identity() { return identity; }

		static matrix4x4 translate(float x, float y, float z) {
			matrix4x4 result = identity;
			result[3][0] = x;
			result[3][1] = y;
			result[3][2] = z;
			return result;
		}

		static matrix4x4 translate(const vector3& vector) {
			return translate(vector.x, vector.y, vector.z);
		}

		static matrix4x4 rotate(const vector3& axis, float angle) {
			matrix4x4 result = identity;

			float c = cos(angle);
			float s = sin(angle);
			const vector3 a = axis.get_normalized();

			result[0][0] = c + (1.0f - c) * a.x * a.x;
			result[0][1] = (1.0f - c) * a.x * a.y + s * a.z;
			result[0][2] = (1.0f - c) * a.x * a.z - s * a.y;

			result[1][0] = (1.0f - c) * a.y * a.x - s * a.z;
			result[1][1] = c + (1.0f - c) * a.y * a.y;
			result[1][2] = (1.0f - c) * a.y * a.z + s * a.x;

			result[2][0] = (1.0f - c) * a.z * a.x + s * a.y;
			result[2][1] = (1.0f - c) * a.z * a.y - s * a.x;
			result[2][2] = c + (1.0f - c) * a.z * a.z;

			return result;
		}

		static matrix4x4 scale(float x, float y, float z) {
			matrix4x4 result = identity;
			result[0][0] = x;
			result[1][1] = y;
			result[2][2] = z;
		}

		static matrix4x4 orthogonal(float left, float right, float bottom, float top) {
			matrix4x4 result = identity;
			result[0][0] = 2.0f / (right - left);
			result[1][1] = 2.0f / (top - bottom);
			result[2][2] = -1.0f;
			result[3][0] = -(right + left) / (right - left);
			result[3][1] = -(top + bottom) / (top - bottom);
			return result;
		}

		static matrix4x4 orthogonal(float left, float right, float bottom, float top, float near, float far) {
			matrix4x4 result = identity;
			result[0][0] = 2.0f / (right - left);
			result[1][1] = 2.0f / (top - bottom);
			result[2][2] = 2.0f / (far - near);
			result[3][0] = -(right + left) / (right - left);
			result[3][1] = -(top + bottom) / (top - bottom);
			result[3][2] = -(far + near) / (far - near);
			return result;
		}

		static matrix4x4 perspective(float fov, float aspect, float near, float far) {
			UE_CORE_ASSERT(aspect > 0, "Aspect is too small.");
			UE_CORE_ASSERT(near > 0, "Near plane is too small.");
			float t = math::tan(math::radians(fov / 2.0f));
			matrix4x4 result;
			result[0][0] = 1.0f / (aspect * t);
			result[1][1] = 1.0f / (t);
			result[2][2] = -(far + near) / (far - near);
			result[2][3] = -1.0f;
			result[3][2] = -(2.0f * far * near) / (far - near);
			return result;
		}

		vector4 get_row(int index) const {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return vector4(_values[0][index], _values[1][index], _values[2][index], _values[3][index]);
		}

		vector4 get_column(int index) const {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return _values[index];
		}

		const float* const to_array() const {
			return &(_values[0][0]);
		}

		vector4& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return _values[index];
		}

		vector4 operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < get_length(), "Index out of range.");
			return _values[index];
		}

		matrix4x4& operator *= (const matrix4x4& other) {
			_values[0] = _values[0] * other[0][0] + _values[1] * other[0][1] + _values[2] * other[0][2] + _values[3] * other[0][3];
			_values[1] = _values[0] * other[1][0] + _values[1] * other[1][1] + _values[2] * other[1][2] + _values[3] * other[1][3];
			_values[2] = _values[0] * other[2][0] + _values[1] * other[2][1] + _values[2] * other[2][2] + _values[3] * other[2][3];
			_values[3] = _values[0] * other[3][0] + _values[1] * other[3][1] + _values[2] * other[3][2] + _values[3] * other[3][3];
			return *this;
		}
	private:
		mutable vector4 _values[4];
	};

	inline matrix4x4 operator * (const matrix4x4& left, const matrix4x4& right) {
		return matrix4x4(left) *= right;
	}
}