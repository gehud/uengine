#pragma once

#include "uengine/math/vector3.h"
#include "uengine/math/vector4.h"
#include "uengine/math/quaternion.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ue {
	struct matrix4x4 {
	public:
		static const matrix4x4 identity;

		matrix4x4() = default;

		matrix4x4(const glm::mat4& matrix) : _value(matrix) { }

		matrix4x4(float x0, float y0, float z0, float w0,
				  float x1, float y1, float z1, float w1,
				  float x2, float y2, float z2, float w2,
				  float x3, float y3, float z3, float w3) : _value(x0, y0, z0, w0,
																   x1, y1, z1, w1,
																   x2, y2, z2, w2,
																   x3, y3, z3, w3) { }

		matrix4x4(const vector4& row0, const vector4& row1, const vector4& row2, const vector4& row3) 
			: _value(static_cast<glm::vec4>(row0), static_cast<glm::vec4>(row1), static_cast<glm::vec4>(row2), static_cast<glm::vec4>(row3)) { }

		static matrix4x4 orthogonal(float left, float right, float bottom, float top) {
			return glm::ortho(left, right, bottom, top);
		}

		static matrix4x4 orthogonal(float left, float right, float bottom, float top, float near, float far) {
			return glm::ortho(left, right, bottom, top, near, far);
		}

		static matrix4x4 perspective(float fov, float aspect, float near, float far) {
			return glm::perspective(glm::radians(fov), aspect, near, far);
		}

		static matrix4x4 translate(const vector3& position) {
			return glm::translate(static_cast<glm::mat4>(identity), static_cast<glm::vec3>(position));
		}

		static matrix4x4 rotate(const quaternion& rotation) {
			return glm::mat4_cast(static_cast<glm::quat>(rotation));
		}

		static matrix4x4 scale(const vector3& scale) {
			return glm::scale(static_cast<glm::mat4>(identity), static_cast<glm::vec3>(scale));
		}

		matrix4x4 get_inverse() const {
			return glm::inverse(_value);
		}

		void inverse() {
			*this = get_inverse();
		}

		vector4 operator [] (int index) const {
			return _value[index];
		}

		matrix4x4 operator *= (const matrix4x4& other) {
			_value *= other._value;
			return *this;
		}

		operator glm::mat4() const {
			return _value;
		}
	private:
		glm::mat4 _value;
	};

	inline matrix4x4 operator * (const matrix4x4& left, const matrix4x4& right) {
		return matrix4x4(left) *= right;
	}
}