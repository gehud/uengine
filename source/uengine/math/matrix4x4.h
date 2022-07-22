#pragma once

#include "uengine/math/vector3.h"
#include "uengine/math/vector4.h"
#include "uengine/math/quaternion.h"

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

		matrix4x4(const vector4& row0,
				  const vector4& row1, 
				  const vector4& row2, 
				  const vector4& row3) : _values { row0, 
												   row1, 
												   row2, 
												   row3 } { }

		static int get_length() { return 4; }

		static matrix4x4 get_identity() { return identity; }

		static matrix4x4 translate(float x, float y, float z) {
			matrix4x4 result = identity;
			result[3][0] = x;
			result[3][1] = y;
			result[3][2] = z;
			return result;
		}

		static matrix4x4 translate(const vector3& translation) {
			return translate(translation.x, translation.y, translation.z);
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

		static matrix4x4 rotate(const quaternion& rotation) {
			matrix4x4 result(identity);

			float qxx = rotation.x * rotation.x;
			float qyy = rotation.y * rotation.y;
			float qzz = rotation.z * rotation.z;
			float qxz = rotation.x * rotation.z;
			float qxy = rotation.x * rotation.y;
			float qyz = rotation.y * rotation.z;
			float qwx = rotation.w * rotation.x;
			float qwy = rotation.w * rotation.y;
			float qwz = rotation.w * rotation.z;

			result[0][0] = 1.0f - 2.0f * (qyy + qzz);
			result[0][1] = 2.0f * (qxy + qwz);
			result[0][2] = 2.0f * (qxz - qwy);

			result[1][0] = 2.0f * (qxy - qwz);
			result[1][1] = 1.0f - 2.0f * (qxx + qzz);
			result[1][2] = 2.0f * (qyz + qwx);

			result[2][0] = 2.0f * (qxz + qwy);
			result[2][1] = 2.0f * (qyz - qwx);
			result[2][2] = 1.0f - 2.0f * (qxx + qyy);

			return result;
		}

		static matrix4x4 scale(float x, float y, float z) {
			matrix4x4 result = identity;
			result[0][0] = x;
			result[1][1] = y;
			result[2][2] = z;
		}

		static matrix4x4 scale(const vector3& scale) {
			return matrix4x4::scale(scale);
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

		float get_determinant() const {
			float m00 = _values[2][2] * _values[3][3] - _values[3][2] * _values[2][3];
			float m01 = _values[2][1] * _values[3][3] - _values[3][1] * _values[2][3];
			float m02 = _values[2][1] * _values[3][2] - _values[3][1] * _values[2][2];
			float m03 = _values[2][0] * _values[3][3] - _values[3][0] * _values[2][3];
			float m04 = _values[2][0] * _values[3][2] - _values[3][0] * _values[2][2];
			float m05 = _values[2][0] * _values[3][1] - _values[3][0] * _values[2][1];

			float a00 = +(_values[1][1] * m00 - _values[1][2] * m01 + _values[1][3] * m02);
			float a01 = -(_values[1][0] * m00 - _values[1][2] * m03 + _values[1][3] * m04);
			float a02 = +(_values[1][0] * m01 - _values[1][1] * m03 + _values[1][3] * m05);
			float a03 = -(_values[1][0] * m02 - _values[1][1] * m04 + _values[1][2] * m05);

			return _values[0][0] * a00 + _values[0][1] * a01 + _values[0][2] * a02 + _values[0][3] * a03;
		}

		matrix4x4 get_inverted() const {
			float m00 = _values[2][2] * _values[3][3] - _values[3][2] * _values[2][3];
			float m02 = _values[1][2] * _values[3][3] - _values[3][2] * _values[1][3];
			float m03 = _values[1][2] * _values[2][3] - _values[2][2] * _values[1][3];
	
			float m04 = _values[2][1] * _values[3][3] - _values[3][1] * _values[2][3];
			float m06 = _values[1][1] * _values[3][3] - _values[3][1] * _values[1][3];
			float m07 = _values[1][1] * _values[2][3] - _values[2][1] * _values[1][3];

			float m08 = _values[2][1] * _values[3][2] - _values[3][1] * _values[2][2];
			float m10 = _values[1][1] * _values[3][2] - _values[3][1] * _values[1][2];
			float m11 = _values[1][1] * _values[2][2] - _values[2][1] * _values[1][2];

			float m12 = _values[2][0] * _values[3][3] - _values[3][0] * _values[2][3];
			float m14 = _values[1][0] * _values[3][3] - _values[3][0] * _values[1][3];
			float m15 = _values[1][0] * _values[2][3] - _values[2][0] * _values[1][3];

			float m16 = _values[2][0] * _values[3][2] - _values[3][0] * _values[2][2];
			float m18 = _values[1][0] * _values[3][2] - _values[3][0] * _values[1][2];
			float m19 = _values[1][0] * _values[2][2] - _values[2][0] * _values[1][2];

			float m20 = _values[2][0] * _values[3][1] - _values[3][0] * _values[2][1];
			float m22 = _values[1][0] * _values[3][1] - _values[3][0] * _values[1][1];
			float m23 = _values[1][0] * _values[2][1] - _values[2][0] * _values[1][1];

			vector4 m0(m00, m00, m02, m03);
			vector4 m1(m04, m04, m06, m07);
			vector4 m2(m08, m08, m10, m11);
			vector4 m3(m12, m12, m14, m15);
			vector4 m4(m16, m16, m18, m19);
			vector4 m5(m20, m20, m22, m23);

			vector4 s0(_values[1][0], _values[0][0], _values[0][0], _values[0][0]);
			vector4 s1(_values[1][1], _values[0][1], _values[0][1], _values[0][1]);
			vector4 s2(_values[1][2], _values[0][2], _values[0][2], _values[0][2]);
			vector4 s3(_values[1][3], _values[0][3], _values[0][3], _values[0][3]);

			vector4 a0(s1 * m0 - s2 * m1 + s3 * m2);
			vector4 a1(s0 * m0 - s2 * m3 + s3 * m4);
			vector4 a2(s0 * m1 - s1 * m3 + s3 * m5);
			vector4 a3(s0 * m2 - s1 * m4 + s2 * m5);
			
			matrix4x4 inverse(+a0[0], -a0[1], +a0[2], -a0[3],
							  -a1[0], +a1[1], -a1[2], +a1[3],
							  +a2[0], -a2[1], +a2[2], -a2[3],
							  -a3[0], +a3[1], -a3[2], +a3[3]);

			float dot = vector4::dot(get_column(0), inverse.get_row(0));
			float one_to_determinant = 1.0f / dot;

			return inverse *= one_to_determinant;
		}

		void inverse() {
			*this = get_inverted();
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

		matrix4x4& operator *= (float number) {
			_values[0] *= number;
			_values[1] *= number;
			_values[2] *= number;
			_values[3] *= number;
			return *this;
		}

		matrix4x4& operator *= (const matrix4x4& other) {
			vector4 a0 = _values[0];
			vector4 a1 = _values[1];
			vector4 a2 = _values[2];
			vector4 a3 = _values[3];

			_values[0] = a0 * other[0][0] + a1 * other[0][1] + a2 * other[0][2] + a3 * other[0][3];
			_values[1] = a0 * other[1][0] + a1 * other[1][1] + a2 * other[1][2] + a3 * other[1][3];
			_values[2] = a0 * other[2][0] + a1 * other[2][1] + a2 * other[2][2] + a3 * other[2][3];
			_values[3] = a0 * other[3][0] + a1 * other[3][1] + a2 * other[3][2] + a3 * other[3][3];

			return *this;
		}

		matrix4x4& operator /= (float number) {
			_values[0] /= number;
			_values[1] /= number;
			_values[2] /= number;
			_values[3] /= number;
			return *this;
		}
	private:
		mutable vector4 _values[4];
	};

	inline matrix4x4 operator * (const matrix4x4& matrix, float number) {
		return matrix4x4(matrix) *= number;
	}

	inline matrix4x4 operator * (const matrix4x4& left, const matrix4x4& right) {
		return matrix4x4(left) *= right;
	}

	inline matrix4x4 operator / (const matrix4x4& matrix, float number) {
		return matrix4x4(matrix) /= number;
	}
}