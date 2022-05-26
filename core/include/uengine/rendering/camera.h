#pragma once

#include "uengine/entity.h"
#include "uengine/transform.h"
#include "uengine/math/matrix4x4.h"

namespace ue 
{
	enum class camera_projection 
	{
		perspective,
		orthographic
	};

	class camera : public component
	{
	private:
		camera_projection _projection;
		float _aspect;
		float _fov = 60.0f;
		float _size = 1.0f;
		float _z_near = 0.0f;
		float _z_far = 1000.0f;
		matrix4x4 _projection_matrix;
		matrix4x4 _view_projection_matrix;
	public:
		camera(camera_projection projection = camera_projection::perspective, float aspect = 1.0f)
			: _projection(projection), _aspect(aspect) { }

		camera_projection get_projection() const { return _projection; }
		void set_projection(camera_projection value) { _projection = value; update_matrices(); }

		float get_aspect() const { return _aspect; }
		void set_aspect(float value) { _aspect = value; update_matrices(); }

		float get_fov() const { return _fov; }
		void set_fov(float value) { _fov = value; update_matrices(); }

		float get_size() const { return _size; }
		void set_size(float value) { _size = value; update_matrices(); }

		float get_z_near() const { return _z_near; }
		void set_z_near(float value) { _z_near = value; update_matrices(); }

		float get_z_far() const { return _z_far; }
		void set_z_far(float value) { _z_far = value; update_matrices(); }

		const matrix4x4& get_projection_matrix() const { return _projection_matrix; }

		const matrix4x4& get_view_projection_matrix() const { return _view_projection_matrix; }
	private:
		void update_matrices() 
		{
			switch (_projection)
			{
			case ue::camera_projection::perspective:
				_projection_matrix = matrix4x4::perspective(glm::radians(_fov), _aspect, _z_near, _z_far);
				break;
			case ue::camera_projection::orthographic:
				_projection_matrix = glm::ortho(-_aspect * _size, _aspect * _size, -1.0f, 1.0f, _z_near, _z_far);
				break;
			}
			_view_projection_matrix = _projection_matrix
				* get_entity().get_component<transform>().get_world_to_local();
		}
	};
}