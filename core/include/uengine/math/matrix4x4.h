#pragma once

#include "uengine/math/vector2.h"
#include "uengine/math/vector3.h"

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
		matrix4x4(const glm::mat4& value) : _value(value) { }

		static matrix4x4 translate(const vector3& translation) 
		{ 
			return glm::translate((glm::mat4)identity, (glm::vec3)translation); 
		}

		static matrix4x4 rotate(const vector3& rotation) 
		{
			return glm::mat4_cast(glm::quat(glm::radians((glm::vec3)rotation)));
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

		float operator [] (const vector2& index) const
		{
			UE_CORE_ASSERT(index.x > -1 && index.x < 4 
				&& index.y > -1 && index.y < 4, "Index out of range.");
			return _value[index.x][index.y];
		}

		float& operator [] (const vector2& index)
		{
			UE_CORE_ASSERT(index.x > -1 && index.x < 4
				&& index.y > -1 && index.y < 4, "Index out of range.");
			return _value[index.x][index.y];
		}

		matrix4x4 operator * (const matrix4x4& other) const { return _value * other._value; }
		
		void operator *= (const matrix4x4& other) { _value *= other._value; }
	};
}