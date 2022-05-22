#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ue 
{
	enum class camera_mode 
	{
		perspective,
		orthographic
	};

	class camera 
	{
	private:
		float _aspect;
		camera_mode _mode = camera_mode::perspective;
		float _fov = 60.0f;
		float _size = 1.0f;
		float _z_near = 0.0f;
		float _z_far = 1000.0f;
		glm::mat4 _view;
		glm::mat4 _projection;
		glm::mat4 _view_projection;
		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _rotation = { 0.0f, 0.0f, 0.0f };
	public:
		camera(float aspect, camera_mode mode = camera_mode::perspective) : _aspect(aspect), _mode(mode)
		{
			recalculate_matrices();
		}

		camera_mode get_mode() const { return _mode; }
		void set_mode(camera_mode value) { _mode = value; recalculate_matrices(); }

		const glm::vec3& get_position() const { return _position; }
		void set_position(const glm::vec3& value) { _position = value; recalculate_matrices(); }

		const glm::vec3& get_rotation() const { return _rotation; }
		void set_rotation(const glm::vec3& value) { _rotation = value; recalculate_matrices(); }

		float get_fov() const { return _fov; }
		void set_fov(float value) { _fov = value; recalculate_matrices(); }

		float get_size() const { return _size; }
		void set_size(float value) { _size = value; recalculate_matrices(); }

		float get_z_near() const { return _z_near; }
		void set_z_near(float value) { _z_near = value; recalculate_matrices(); }

		float get_z_far() const { return _z_far; }
		void set_z_far(float value) { _z_far = value; recalculate_matrices(); }

		const glm::mat4& get_view_projection() const { return _view_projection; }
	private:
		void recalculate_matrices() 
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, _position.y, -_position.z));
			transform = glm::rotate(transform, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(-_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			_view = glm::inverse(transform);
			switch (_mode)
			{
			case ue::camera_mode::perspective:
				_projection = glm::perspective(glm::radians(_fov), _aspect, _z_near, _z_far);
				break;
			case ue::camera_mode::orthographic:
				_projection = glm::ortho(-_aspect * _size, _aspect * _size, -1.0f, 1.0f, _z_near, _z_far);
				break;
			}
			_view_projection = _projection * _view;
		}
	};
}