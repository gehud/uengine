#pragma once

#include "uengine/math/vector3.h"
#include "uengine/math/vector4.h"
#include "uengine/math/quaternion.h"

namespace ue {
	struct matrix4x4 {
	public:

		constexpr matrix4x4() : matrix4x4(1, 0, 0, 0,
										  0, 1, 0, 0,		
										  0, 0, 1, 0, 
										  0, 0, 0, 1) { }

		constexpr matrix4x4(float scalar) : matrix4x4(scalar, 0, 0, 0,
													  0, scalar, 0, 0,
													  0, 0, scalar, 0,
													  0, 0, 0, scalar) { }

		constexpr matrix4x4(float x0, float y0, float z0, float w0,
							float x1, float y1, float z1, float w1,
							float x2, float y2, float z2, float w2,
							float x3, float y3, float z3, float w3) : _values{ {x0, y0, z0, w0},
																			   {x1, y1, z1, w1},
																			   {x2, y2, z2, w2},
																			   {x3, y3, z3, w3} } { }

		constexpr matrix4x4(const vector4f& row0,
							const vector4f& row1, 
							const vector4f& row2, 
							const vector4f& row3) : _values{row0, row1, row2, row3} { }

		static constexpr int length() { return 4; }

		static constexpr matrix4x4 identity() { return matrix4x4(1, 0, 0, 0,
																 0, 1, 0, 0,
																 0, 0, 1, 0,
																 0, 0, 0, 1); }

		static matrix4x4 orthogonal(float left, float right, float bottom, float top) {
			matrix4x4 result;
			result[0][0] = 2 / (right - left);
			result[1][1] = 2 / (top - bottom);
			result[2][2] = -1;
			result[3][0] = -(right + left) / (right - left);
			result[3][1] = -(top + bottom) / (top - bottom);
			return result;
		}

		static matrix4x4 orthogonal(float left, float right, float bottom, float top, float near, float far) {
			matrix4x4 result;
			result[0][0] = 2 / (right - left);
			result[1][1] = 2 / (top - bottom);
			result[2][2] = -2 / (far - near);
			result[3][0] = -(right + left) / (right - left);
			result[3][1] = -(top + bottom) / (top - bottom);
			result[3][2] = -(far + near) / (far - near);
			return result;
		}

		static matrix4x4 perspective(float fov, float aspect, float near, float far) {
			UE_CORE_ASSERT(math::abs(aspect - math::epsilon) > 0, "Aspect is too small.");
			float t = math::tan(math::radians(fov) / 2);
			matrix4x4 result(0);
			result[0][0] = 1 / (aspect * t);
			result[1][1] = 1 / (t);
			result[2][2] = -(far + near) / (far - near);
			result[2][3] = -1;
			result[3][2] = -(2 * far * near) / (far - near);
			return result;
		}

		static matrix4x4 translate(const vector3f& position) {
			matrix4x4 result;
			result[3][0] = position.x;
			result[3][1] = position.y;
			result[3][2] = position.z;
			return result;
		}

		static matrix4x4 rotate(const quaternion& rotation) {
			matrix4x4 result;

			float qxx = rotation.x * rotation.x;
			float qyy = rotation.y * rotation.y;
			float qzz = rotation.z * rotation.z;
			float qxz = rotation.x * rotation.z;
			float qxy = rotation.x * rotation.y;
			float qyz = rotation.y * rotation.z;
			float qwx = rotation.w * rotation.x;
			float qwy = rotation.w * rotation.y;
			float qwz = rotation.w * rotation.z;

			result[0][0] = 1 - 2 * (qyy + qzz);
			result[0][1] = 2 * (qxy + qwz);
			result[0][2] = 2 * (qxz - qwy);
			
			result[1][0] = 2 * (qxy - qwz);
			result[1][1] = 1 - 2 * (qxx + qzz);
			result[1][2] = 2 * (qyz + qwx);
			
			result[2][0] = 2 * (qxz + qwy);
			result[2][1] = 2 * (qyz - qwx);
			result[2][2] = 1 - 2 * (qxx + qyy);

			return result;
		}

		static matrix4x4 scale(const vector3f& scale) {
			matrix4x4 result;
			result[3][0] = scale.x;
			result[3][1] = scale.y;
			result[3][2] = scale.z;
			return result;
		}

		constexpr matrix4x4 inverse() const {
			float m00 = _values[2][2] * _values[3][3] - _values[3][2] * _values[2][3];
			float m01 = _values[1][2] * _values[3][3] - _values[3][2] * _values[1][3];
			float m02 = _values[1][2] * _values[2][3] - _values[2][2] * _values[1][3];

			float m03 = _values[2][1] * _values[3][3] - _values[3][1] * _values[2][3];
			float m04 = _values[1][1] * _values[3][3] - _values[3][1] * _values[1][3];
			float m05 = _values[1][1] * _values[2][3] - _values[2][1] * _values[1][3];

			float m06 = _values[2][1] * _values[3][2] - _values[3][1] * _values[2][2];
			float m07 = _values[1][1] * _values[3][2] - _values[3][1] * _values[1][2];
			float m08 = _values[1][1] * _values[2][2] - _values[2][1] * _values[1][2];

			float m09 = _values[2][0] * _values[3][3] - _values[3][0] * _values[2][3];
			float m10 = _values[1][0] * _values[3][3] - _values[3][0] * _values[1][3];
			float m11 = _values[1][0] * _values[2][3] - _values[2][0] * _values[1][3];

			float m12 = _values[2][0] * _values[3][2] - _values[3][0] * _values[2][2];
			float m13 = _values[1][0] * _values[3][2] - _values[3][0] * _values[1][2];
			float m14 = _values[1][0] * _values[2][2] - _values[2][0] * _values[1][2];

			float m15 = _values[2][0] * _values[3][1] - _values[3][0] * _values[2][1];
			float m16 = _values[1][0] * _values[3][1] - _values[3][0] * _values[1][1];
			float m17 = _values[1][0] * _values[2][1] - _values[2][0] * _values[1][1];

			vector4f v0(m00, m00, m01, m02);
			vector4f v1(m03, m03, m04, m05);
			vector4f v2(m06, m06, m07, m08);
			vector4f v3(m09, m09, m10, m11);
			vector4f v4(m12, m12, m13, m14);
			vector4f v5(m15, m15, m16, m17);

			vector4f s0(_values[1][0], _values[0][0], _values[0][0], _values[0][0]);
			vector4f s1(_values[1][1], _values[0][1], _values[0][1], _values[0][1]);
			vector4f s2(_values[1][2], _values[0][2], _values[0][2], _values[0][2]);
			vector4f s3(_values[1][3], _values[0][3], _values[0][3], _values[0][3]);

			vector4f a0(s1 * v0 - s2 * v1 + s3 * v2);
			vector4f a1(s0 * v0 - s2 * v3 + s3 * v4);
			vector4f a2(s0 * v1 - s1 * v3 + s3 * v5);
			vector4f a3(s0 * v2 - s1 * v4 + s2 * v5);

			vector4f sign_a(+1, -1, +1, -1);
			vector4f sign_b(-1, +1, -1, +1);
			matrix4x4 result(a0 * sign_a, a1 * sign_b, a2 * sign_a, a3 * sign_b);

			vector4f row(result[0][0], result[1][0], result[2][0], result[3][0]);

			float dot = vector4f::dot(_values[0], row);

			float f = 1.0f / dot;

			return result *= f;
		}

		constexpr const float* data() const {
			return &_values[0].x;
		}

		constexpr vector4f& operator [] (int index) {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out of range.");
			return _values[index];
		}

		constexpr vector4f operator [] (int index) const {
			UE_CORE_ASSERT(index >= 0 && index < length(), "Index out of range.");
			return _values[index];
		}

		matrix4x4& operator *= (float scalar) {
			_values[0] *= scalar;
			_values[1] *= scalar;
			_values[2] *= scalar;
			_values[3] *= scalar;
			return *this;
		}

		matrix4x4& operator *= (const matrix4x4& other) {
			vector4f v00 = _values[0];
			vector4f v01 = _values[1];
			vector4f v02 = _values[2];
			vector4f v03 = _values[3];

			vector4f v10 = other[0];
			vector4f v11 = other[1];
			vector4f v12 = other[2];
			vector4f v13 = other[3];

			_values[0] = v00 * v10[0] + v01 * v10[1] + v02 * v10[2] + v03 * v10[3];
			_values[1] = v00 * v11[0] + v01 * v11[1] + v02 * v11[2] + v03 * v11[3];
			_values[2] = v00 * v12[0] + v01 * v12[1] + v02 * v12[2] + v03 * v12[3];
			_values[3] = v00 * v13[0] + v01 * v13[1] + v02 * v13[2] + v03 * v13[3];

			return *this;
		}
	private:
		mutable vector4f _values[4];
	};

	inline matrix4x4 operator * (const matrix4x4& m, float s) {
		matrix4x4 result(m);
		result[0] *= s;
		result[1] *= s;
		result[2] *= s;
		result[3] *= s;
		return result;
	}

	inline matrix4x4 operator * (const matrix4x4& l, const matrix4x4& r) {
		vector4f v00 = l[0];
		vector4f v01 = l[1];
		vector4f v02 = l[2];
		vector4f v03 = l[3];
		
		vector4f v10 = r[0];
		vector4f v11 = r[1];
		vector4f v12 = r[2];
		vector4f v13 = r[3];

		matrix4x4 result;
		result[0] = v00 * v10[0] + v01 * v10[1] + v02 * v10[2] + v03 * v10[3];
		result[1] = v00 * v11[0] + v01 * v11[1] + v02 * v11[2] + v03 * v11[3];
		result[2] = v00 * v12[0] + v01 * v12[1] + v02 * v12[2] + v03 * v12[3];
		result[3] = v00 * v13[0] + v01 * v13[1] + v02 * v13[2] + v03 * v13[3];
		return result;
	}
}