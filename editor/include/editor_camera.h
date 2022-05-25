#pragma once

#include <uengine/rendering/camera.h>
#include <uengine/input.h>
#include <uengine/keycodes.h>
#include <uengine/time.h>
#include <uengine/log.h>
#include <uengine/rendering/gl.h>
#include <uengine/rendering/vertex_buffer.h>
#include <uengine/rendering/index_buffer.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <algorithm>

class editor_camera 
{
private:
	float _aspect;
	ue::camera_projection _mode = ue::camera_projection::perspective;
	float _fov = 60.0f;
	float _size = 1.0f;
	float _z_near = 0.0f;
	float _z_far = 1000.0f;
	glm::mat4 _view;
	glm::mat4 _projection;
	glm::mat4 _view_projection;
	glm::vec3 _position = { 0.0f, 0.0f, -1.0f };
	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _sensitivity = 0.1f;
	float _speed = 1.0f;
	glm::vec3 _right = { 1.0f, 0.0f, 0.0f };
	glm::vec3 _up = { 0.0f, 1.0f, 0.0f };
	glm::vec3 _forward = { 0.0f, 0.0f, 1.0f };
public:
	editor_camera(float aspect, ue::camera_projection mode = ue::camera_projection::perspective) : _aspect(aspect), _mode(mode)
	{
		recalculate_matrices();
	}

	ue::camera_projection get_mode() const { return _mode; }
	void set_mode(ue::camera_projection value) { _mode = value; recalculate_matrices(); }

	float get_aspect() const { return _aspect; }
	void set_aspect(float value) { _aspect = value; recalculate_matrices(); }

	float get_fov() const { return _fov; }
	void set_fov(float value) { _fov = value; recalculate_matrices(); }

	float get_size() const { return _size; }
	void set_size(float value) { _size = value; recalculate_matrices(); }

	float get_z_near() const { return _z_near; }
	void set_z_near(float value) { _z_near = value; recalculate_matrices(); }

	float get_z_far() const { return _z_far; }
	void set_z_far(float value) { _z_far = value; recalculate_matrices(); }

	const glm::mat4& get_view_projection() const { return _view_projection; }

	void update() 
	{
		if (ue::input::is_mouse_button_pressed(UE_MOUSE_BUTTON_RIGHT))
		{
			glm::vec2 delta = ue::input::get_mouse_delta();
			float sign = _up.y < 0.0f ? -1.0f : 1.0f;
			_yaw += sign * delta.x * _sensitivity;
			if (_yaw > 360.0f)
				_yaw -= 360.0f;
			else if (_yaw < -360.0f)
				_yaw += 360.0f;
			_pitch = std::clamp(_pitch + delta.y * _sensitivity, -90.0f, 90.0f);
			_right =	glm::vec3(_view[0][0], _view[0][1], _view[0][2]);
			_up =		glm::vec3(_view[1][0], _view[1][1], _view[1][2]);
			_forward =	glm::vec3(_view[2][0], _view[2][1], _view[2][2]);
		}
		if (ue::input::is_key_pressed(UE_KEY_W))
			move_forward();
		else if (ue::input::is_key_pressed(UE_KEY_S))
			move_back();
		if (ue::input::is_key_pressed(UE_KEY_A))
			move_left();
		else if (ue::input::is_key_pressed(UE_KEY_D))
			move_right();
		if (ue::input::is_key_pressed(UE_KEY_Q))
			move_down();
		else if (ue::input::is_key_pressed(UE_KEY_E))
			move_up();
		recalculate_matrices();
	}
private:
	void move_forward()
	{
		_position += _forward * _speed * ue::time::get_delta();
	}

	void move_back() 
	{
		_position -= _forward * _speed * ue::time::get_delta();
	}
	
	void move_right() 
	{
		_position += _right * _speed * ue::time::get_delta();
	}

	void move_left() 
	{
		_position -= _right * _speed * ue::time::get_delta();
	}

	void move_up() 
	{
		_position += _up * _speed * ue::time::get_delta();
	}

	void move_down() 
	{
		_position -= _up * _speed * ue::time::get_delta();
	}

	glm::quat get_orientation() 
	{
		return glm::quat(glm::vec3(glm::radians(-_pitch), glm::radians(-_yaw), 0.0f));
	}

	void recalculate_matrices()
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(_position.x, _position.y, -_position.z));
		transform *= glm::toMat4(get_orientation());

		_view = glm::inverse(transform);
		switch (_mode)
		{
		case ue::camera_projection::perspective:
			_projection = glm::perspective(glm::radians(_fov), _aspect, _z_near, _z_far);
			break;
		case ue::camera_projection::orthographic:
			_projection = glm::ortho(-_aspect * _size, _aspect * _size, -1.0f, 1.0f, _z_near, _z_far);
			break;
		}
		_view_projection = _projection * _view;
	}
};