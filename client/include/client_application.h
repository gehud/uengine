#pragma once

#include <uengine.h>

using namespace ue;

class camera_controller : public script
{
private:
	camera* _camera;
	transform* _transform;
	float _rotation_x = 0.0f;
public:
	camera_controller(const entity& entity) : script(entity) 
	{
		_transform = &get_entity().get_component<transform>();
		_camera = &get_entity().add_component<camera>();
		_camera->set_aspect(16.0f / 9.0f);
		_transform->set_position({ 0.0f, 0.0f, 2.0f });
	}
protected:
	void on_update() override 
	{
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
	}
};

class client_application : public application
{
private:
	reference<mesh> _mesh;
	reference<texture_2d> _texture;
	reference<shader> _shader;
	scene _scene;
	reference<entity> _entity;
public:
	client_application()
	{
		float vertices[24 * 8] = 
		{
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
										 
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
								  		  
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
								  		  	    
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
								  		  	    
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
								  		 
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f
		};

		unsigned int indices[36] = 
		{ 
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,
			16, 17, 18, 16, 18, 19,
			20, 21, 22, 20, 22, 23,
		};

		_mesh = mesh::create();

		_mesh->set_vertex_buffer_params(24, { 
			{ "a_Position", vertex_attribute_format::float32, 3 },
			{ "a_Normal", vertex_attribute_format::float32, 3 },
			{ "a_UV", vertex_attribute_format::float32, 2 } 
		});
		_mesh->set_vertex_buffer_data(vertices);

		_mesh->set_index_buffer_params(36);
		_mesh->set_index_buffer_data(indices);

		_texture = texture_2d::create("assets/textures/checkerboard.png");
		_texture->set_filter_mode(texture_filter_mode::nearest);

		_shader = shader::create("assets/shaders/texture.glsl");
		_shader->set_int("u_Texture", 0);

		scene_manager::add_scene(_scene);
		scene_manager::set_active_scene(_scene);

		_entity = entity_manager::create();
		_entity->add_component<camera_controller>();
		system_manager::add_system<script_system<camera_controller>>();
	}

	void on_update() override
	{
		gl::clear_color(0.1f, 0.1f, 0.1f, 1.0f);
		gl::clear();

		_shader->bind();
		_texture->bind();
		_shader->set_vector3("u_LightPosition", vector3(5.0f, 5.0f, 5.0f));
		_shader->set_vector3("u_ViewPosition", _entity->get_component<transform>().get_position());
		_shader->set_vector4("u_Color", vector4(1.0f, 0.0f, 0.0f, 0.0f));
		_shader->set_matrix4x4("u_ViewProjection", _entity->get_component<camera>().get_projection_matrix() 
			* _entity->get_component<transform>().get_world_to_local());
		graphics::draw_mesh(_mesh);
	}
};