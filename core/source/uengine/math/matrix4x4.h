#pragma once

#include "vector4.h"
#include "vector3.h"
#include "matrix3x3.h"

namespace ue {
	struct matrix4x4 {
	public:
		static const matrix4x4 zero;
		static const matrix4x4 one;
		static const matrix4x4 identity;

		matrix4x4() = default;

		matrix4x4(float x0, float y0, float z0, float w0,
				  float x1, float y1, float z1, float w1,
				  float x2, float y2, float z2, float w2,
				  float x3, float y3, float z3, float w3) {
#if defined(UE_MATRICES_ROW_MAJOR)
			_values[0][0] = x0;  _values[0][1] = y0;  _values[0][2] = z0;  _values[0][3] = w0;
			_values[1][0] = x1;  _values[1][1] = y1;  _values[1][2] = z1;  _values[1][3] = w1;
			_values[2][0] = x2;  _values[2][1] = y2;  _values[2][2] = z2;  _values[2][3] = w2;
			_values[3][0] = x3;  _values[3][1] = y3;  _values[3][2] = z3;  _values[3][3] = w3;
#elif defined(UE_MATRICES_COLUMN_MAJOR)
			_values[0][0] = x0;  _values[1][0] = y0;  _values[2][0] = z0;  _values[3][0] = w0;
			_values[0][1] = x1;  _values[1][1] = y1;  _values[2][1] = z1;  _values[3][1] = w1;
			_values[0][2] = x2;  _values[1][2] = y2;  _values[2][2] = z2;  _values[3][2] = w2;
			_values[0][3] = x3;  _values[1][3] = y3;  _values[2][3] = z3;  _values[3][3] = w3;
#endif
		}

		static matrix4x4 get_zero() { return zero; }
		static matrix4x4 get_one() { return one; }
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
			UE_CORE_ASSERT(math::abs(math::epsilon - aspect) > 0, "Aspect is too small.");
			UE_CORE_ASSERT(near > 0, "Near plane is too small.");
			float t = math::tan(math::radians(fov / 2.0f));
			matrix4x4 result = zero;
			result[0][0] = 1.0f / (aspect * t);
			result[1][1] = 1.0f / (t);
			result[2][2] = -(far + near) / (far - near);
			result[2][3] = -1.0f;
			result[3][2] = -(2.0f * far * near) / (far - near);
			return result;
		}

		float determinant() const {
			// Row method.
			float m00 = matrix3x3(_values[1][1], _values[1][2], _values[1][3],
								  _values[2][1], _values[2][2], _values[2][3],
								  _values[3][1], _values[3][2], _values[3][3]).determinant();
			float m01 = matrix3x3(_values[1][0], _values[1][2], _values[1][3],
								  _values[2][0], _values[2][2], _values[2][3],
								  _values[3][0], _values[3][2], _values[3][3]).determinant();
			float m02 = matrix3x3(_values[1][0], _values[1][1], _values[1][3],
								  _values[2][0], _values[2][1], _values[2][3],
								  _values[3][0], _values[3][1], _values[3][3]).determinant();
			float m03 = matrix3x3(_values[1][0], _values[1][1], _values[1][2],
								  _values[2][0], _values[2][1], _values[2][2],
								  _values[3][0], _values[3][1], _values[3][2]).determinant();
			return _values[0][0] * m00 + -_values[0][1] * m01 + _values[0][2] * m02 + -_values[0][3] * m03;
		}

		matrix4x4 get_transposed() const {
			return matrix4x4(_values[0][0], _values[1][0], _values[2][0], _values[3][0],
							 _values[0][1], _values[1][1], _values[2][1], _values[3][1], 
							 _values[0][2], _values[1][2], _values[2][2], _values[3][2], 
							 _values[0][3], _values[1][3], _values[2][3], _values[3][3]);
		}

		void transpose() {
			*this = get_transposed();
		}

		vector4 get_row(uint32 index) const {
			UE_CORE_ASSERT(index <= 3, "Index out of range.");
			return vector4(_values[0][index], _values[1][index], _values[2][index], _values[3][index]);
		}

		vector4 get_column(uint32 index) const {
			UE_CORE_ASSERT(index <= 3, "Index out of range.");
			return _values[index];
		}

		const float* const to_array() const {
			return &(_values[0][0]);
		}

		vector4 operator [] (uint32 index) const {
			UE_CORE_ASSERT(index <= 3, "Index out of range.");
			return _values[index];
		}

		vector4& operator [] (uint32 index) {
			UE_CORE_ASSERT(index <= 3, "Index out of range.");
			return _values[index];
		}

		matrix4x4& operator *= (const matrix4x4& other) {
			_values[0][0] = vector4::dot(get_row(0), other.get_column(0));
			_values[0][1] = vector4::dot(get_row(0), other.get_column(1));
			_values[0][2] = vector4::dot(get_row(0), other.get_column(2));
			_values[0][3] = vector4::dot(get_row(0), other.get_column(3));
												
			_values[1][0] = vector4::dot(get_row(1), other.get_column(0));
			_values[1][1] = vector4::dot(get_row(1), other.get_column(1));
			_values[1][2] = vector4::dot(get_row(1), other.get_column(2));
			_values[1][3] = vector4::dot(get_row(1), other.get_column(3));
												
			_values[2][0] = vector4::dot(get_row(2), other.get_column(0));
			_values[2][1] = vector4::dot(get_row(2), other.get_column(1));
			_values[2][2] = vector4::dot(get_row(2), other.get_column(2));
			_values[2][3] = vector4::dot(get_row(2), other.get_column(3));
												
			_values[3][0] = vector4::dot(get_row(3), other.get_column(0));
			_values[3][1] = vector4::dot(get_row(3), other.get_column(1));
			_values[3][2] = vector4::dot(get_row(3), other.get_column(2));
			_values[3][3] = vector4::dot(get_row(3), other.get_column(3));

			return *this;
		}
	private:
		mutable vector4 _values[4];
	};

	inline matrix4x4 operator * (const matrix4x4& left, const matrix4x4& right) {
		float x0 = vector4::dot(left.get_row(0), right.get_column(0));
		float y0 = vector4::dot(left.get_row(0), right.get_column(1));
		float z0 = vector4::dot(left.get_row(0), right.get_column(2));
		float w0 = vector4::dot(left.get_row(0), right.get_column(3));

		float x1 = vector4::dot(left.get_row(1), right.get_column(0));
		float y1 = vector4::dot(left.get_row(1), right.get_column(1));
		float z1 = vector4::dot(left.get_row(1), right.get_column(2));
		float w1 = vector4::dot(left.get_row(1), right.get_column(3));

		float x2 = vector4::dot(left.get_row(2), right.get_column(0));
		float y2 = vector4::dot(left.get_row(2), right.get_column(1));
		float z2 = vector4::dot(left.get_row(2), right.get_column(2));
		float w2 = vector4::dot(left.get_row(2), right.get_column(3));

		float x3 = vector4::dot(left.get_row(3), right.get_column(0));
		float y3 = vector4::dot(left.get_row(3), right.get_column(1));
		float z3 = vector4::dot(left.get_row(3), right.get_column(2));
		float w3 = vector4::dot(left.get_row(3), right.get_column(3));

		return matrix4x4(x0, y0, z0, w0,
						 x1, y1, z1, w1,
						 x2, y2, z2, w2,
						 x3, y3, z3, w3);
	}
}