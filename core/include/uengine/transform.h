#pragma once

#include "uengine/math/vector3.h"
#include "uengine/math/quaternion.h"
#include "uengine/math/matrix4x4.h"

namespace ue 
{
	class transform 
	{
	private:
		vector3 _position = { 0.0f, 0.0f, 0.0f };
		vector3 __local_position = { 0.0f, 0.0f, 0.0f };
		quaternion _rotation = quaternion::identity;
		quaternion _local_rotation = quaternion::identity;
		vector3 _scale = { 1.0f, 1.0f, 1.0f };
		vector3 _local_scale = { 1.0f, 1.0f, 1.0f };
		matrix4x4 _local_to_world = matrix4x4::identity;
		matrix4x4 _world_to_local = matrix4x4::identity;
	public:
		transform() = default;
		transform(const transform& other) = default;

		vector3 get_position() const { return _position; }
		void set_position(const vector3& value) { _position = value; update_matrices(); }

		quaternion get_rotation() const { return _rotation; }
		void set_rotation(const quaternion& value) { _rotation = value; update_matrices(); }

		vector3 get_euler_angles() const { return _rotation.get_euler_angles(); }
		void set_euler_angles(const vector3& value) { _rotation.set_euler_angles(value); update_matrices(); }

		vector3 get_scale() const { return _scale; }
		void set_scale(const vector3& value) { _scale = value; }

		vector3 get_right() const 
		{ 
			return vector3(_local_to_world[{0, 0}], _local_to_world[{0, 1}], _local_to_world[{0, 2}]); 
		}

		vector3 get_up() const
		{
			return vector3(_local_to_world[{1, 0}], _local_to_world[{1, 1}], _local_to_world[{1, 2}]);
		}

		vector3 get_forward() const
		{
			return vector3(_local_to_world[{2, 0}], _local_to_world[{2, 1}], _local_to_world[{2, 2}]);
		}

		matrix4x4 get_local_to_world() const { return _local_to_world; }

		matrix4x4 get_world_to_local() const { return _world_to_local; }
	private:
		void update_matrices() 
		{
			_local_to_world = matrix4x4::translate(_position)
				* matrix4x4::rotate(_rotation) * matrix4x4::scale(_scale);
			_world_to_local = matrix4x4::inverse(_local_to_world);
		}
	};
}