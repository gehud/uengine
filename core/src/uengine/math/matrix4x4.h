#pragma once

#include "vector3.h"
#include "quaternion.h"
#include "vector2_int.h"

#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ue 
{
	struct matrix4x4 
	{
	public:
		static const matrix4x4 identity;
	private:
		glm::mat4 _value;
	public:
		matrix4x4() : _value(0.0f) { }

		matrix4x4(const glm::mat4& value) : _value(value) { }

		static matrix4x4 perspective(float fov, float aspect, float z_near, float z_far) 
		{
			return glm::perspective(fov, aspect, z_near, z_far);
		}

		static matrix4x4 ortho(float left, float right, float bottom, float top) 
		{
			return glm::ortho(left, right, bottom, top);
		}

		static matrix4x4 ortho(float left, float right, float bottom, float top, float z_near, float z_far)
		{
			return glm::ortho(left, right, bottom, top, z_near, z_far);
		}

		static matrix4x4 translate(const vector3& translation) 
		{ 
			return glm::translate((glm::mat4)identity, (glm::vec3)translation); 
		}

		static matrix4x4 rotate(const quaternion& rotation) 
		{
			return glm::mat4_cast((glm::quat)rotation);
		}

		static matrix4x4 scale(const vector3& scale) 
		{
			return glm::scale((glm::mat4)identity, (glm::vec3)scale);
		}

		static matrix4x4 inverse(const matrix4x4& matrix) 
		{
			return glm::inverse((glm::mat4)matrix);
		}

		operator glm::mat4() const { return _value; }

		float operator [] (const vector2_int& index) const
		{
			UE_CORE_ASSERT(index.x >= 0 && index.x <= 3 
				&& index.y >= 0 && index.y <= 3, "Index out of range.");
			return _value[index.x][index.y];
		}

		float& operator [] (const vector2_int& index)
		{
			UE_CORE_ASSERT(index.x >= 0 && index.x <= 3
				&& index.y >= 0 && index.y <= 3, "Index out of range.");
			return _value[index.x][index.y];
		}

		matrix4x4 operator * (const matrix4x4& other) const { return _value * other._value; }
		
		void operator *= (const matrix4x4& other) { _value *= other._value; }
	};
}