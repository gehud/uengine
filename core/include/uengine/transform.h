#pragma once

#include "uengine/math/vector3.h"
#include "uengine/math/matrix4x4.h"

namespace ue 
{
	class transform 
	{
	private:
		vector3 _position = { 0.0f, 0.0f, 0.0f };
		vector3 _rotation = { 0.0f, 0.0f, 0.0f };
		vector3 _scale = { 1.0f, 1.0f, 1.0f };
	public:
		transform() = default;
		transform(const transform& other) = default;

		vector3 get_position() const { return _position; }
		void set_position(const vector3& value) { _position = value; }

		vector3 get_rotation() const { return _rotation; }
		void set_rotation(const vector3& value) { _rotation = value; }

		vector3 get_scale() const { return _scale; }
		void set_scale(const vector3& value) { _scale = value; }

		matrix4x4 get_local_to_world() const 
		{
			return matrix4x4::inverse(matrix4x4::translate(_position)
				* matrix4x4::rotate(_rotation) * matrix4x4::scale(_scale));
		}

		matrix4x4 get_world_to_local() const 
		{
			return matrix4x4::translate(_position)
				* matrix4x4::rotate(_rotation) * matrix4x4::scale(_scale);
		}
	};
}