#pragma once

#include <uengine.h>

using namespace ue;

class client_application : public application
{
private:
	/*std::shared_ptr<vertex_array> _vertex_array;
	std::shared_ptr<vertex_buffer> _z_vertex_buffer;
	std::shared_ptr<index_buffer> _index_buffer;
	std::shared_ptr<texture_2d> _texture;
	std::shared_ptr<shader> _shader;
	scene _scene;
	entity _entity;
	transform* _transform;
	camera* _camera;
	float _rotation_x = 0.0f;*/
public:
	client_application()
	{
		/*_vertex_array = vertex_array::create();
		_vertex_array->bind();

		float vertices[4 * 5] = 
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
		};
		_z_vertex_buffer = vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float), sizeof(float));
		_z_vertex_buffer->set_layout({
			{ vertex_attribute_format::float3, "a_Position"},
			{ vertex_attribute_format::float2, "a_UV"}
		});

		unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };

		_index_buffer = index_buffer::create(indices, sizeof(indices) / sizeof(int), sizeof(int));

		_texture = texture_2d::create("assets/textures/checkerboard.png");
		_texture->set_filter_mode(texture_filter_mode::nearest);

		_shader = shader::create("assets/shaders/texture.glsl");
		_shader->set_int(0, "u_Texture");

		_entity = entity(_scene);
		_transform = &_entity.get_component<transform>();
		_camera = &_entity.add_component<camera>();
		_camera->set_aspect(16.0f / 9.0f);
		_transform->set_position({ 0.0f, 0.0f, 1.0f });
		add_scene(_scene);*/
	}

	void on_update() override
	{
		/*gl::clear_color(0.1f, 0.1f, 0.1f, 1.0f);
		gl::clear();

		if (input::get_mouse_button(UE_MOUSE_BUTTON_RIGHT))
		{
			vector2 delta = input::get_mouse_position_delta();
			_transform->rotate(quaternion::euler_angles(vector3::get_down() * delta.x * 0.1f));
			_rotation_x = std::clamp(_rotation_x - delta.y * 0.1f, -90.0f, 90.0f);
			_transform->set_local_euler_angles(vector3::get_right() * _rotation_x);
		}

		if (input::get_key(UE_KEY_W))
			_transform->translate(-_transform->get_forward() * time::get_delta());
		else if (input::get_key(UE_KEY_S))
			_transform->translate(_transform->get_forward() * time::get_delta());
		if (input::get_key(UE_KEY_D))
			_transform->translate(_transform->get_right() * time::get_delta());
		else if (input::get_key(UE_KEY_A))
			_transform->translate(-_transform->get_right() * time::get_delta());
		if (input::get_key(UE_KEY_E))
			_transform->translate(_transform->get_up() * time::get_delta());
		else if (input::get_key(UE_KEY_Q))
			_transform->translate(-_transform->get_up() * time::get_delta());

		_shader->bind();
		_texture->bind();
		_shader->set_vector4(vector4(1.0f, 0.0f, 0.0f, 0.0f), "u_Color");
		_shader->set_matrix4x4(_camera->get_projection_matrix() * _transform->get_world_to_local(), "u_ViewProjection");
		_vertex_array->bind();
		gl::draw_elements(gl::get_triangles_mode(), _index_buffer->get_count(), _index_buffer->get_type());*/
	}
};