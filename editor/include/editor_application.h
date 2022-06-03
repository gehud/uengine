#pragma once

#include "game_window.h"
#include "scene_hierarchy_window.h"

#include <uengine.h>

#include <imgui.h>
#include <imgui_internal.h>

class editor_application : public ue::application
{
private:
	std::shared_ptr<ue::vertex_array> _vertex_array;
	std::shared_ptr<ue::vertex_buffer> _vertex_buffer;
	std::shared_ptr<ue::index_buffer> _index_buffer;
	std::shared_ptr<ue::framebuffer> _framebuffer;
	std::shared_ptr<ue::texture_2d> _texture;
	std::shared_ptr<ue::shader> _shader;
	ue::scene _scene;
	ue::entity _entity;
	ue::transform* _transform;
	ue::camera* _camera;
	float _rotation_x = 0.0f;
	game_window _game_window;
	scene_hierarchy_window _scene_hierarchy_window;
public:
	editor_application() : _game_window(_framebuffer)
	{
		_vertex_array = ue::vertex_array::create();
		_vertex_array->bind();

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

		_vertex_buffer = ue::vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float), sizeof(float));
		_vertex_buffer->set_layout({
			{ ue::vertex_attribute_format::float3, "a_Position"},
			{ ue::vertex_attribute_format::float3, "a_Normal"},
			{ ue::vertex_attribute_format::float2, "a_UV"}
		});

		unsigned int indices[36] =
		{
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,
			16, 17, 18, 16, 18, 19,
			20, 21, 22, 20, 22, 23,
		};

		_index_buffer = ue::index_buffer::create(indices, sizeof(indices) / sizeof(int), sizeof(int));

		_texture = ue::texture_2d::create("assets/textures/checkerboard.png");
		_texture->set_filter_mode(ue::texture_filter_mode::nearest);

		_shader = ue::shader::create("assets/shaders/texture.glsl");
		_shader->set_int("u_Texture", 0);

		_entity = ue::entity(_scene);
		_transform = &_entity.get_component<ue::transform>();
		_camera = &_entity.add_component<ue::camera>();
		_camera->set_aspect(16.0f / 9.0f);
		_transform->set_position({ 0.0f, 0.0f, 2.0f });
		add_scene(_scene);

		_framebuffer = ue::framebuffer::create({ 1280, 720 });
	}

	void on_update() override
	{
		_framebuffer->bind();


		ue::gl::clear_color(0.1f, 0.1f, 0.1f, 1.0f);
		ue::gl::clear();

		if (ue::input::get_mouse_button(UE_MOUSE_BUTTON_RIGHT))
		{
			ue::vector2 delta = ue::input::get_mouse_position_delta();
			_transform->rotate(ue::quaternion::euler_angles(ue::vector3::get_down() * delta.x * 0.1f));
			_rotation_x = std::clamp(_rotation_x - delta.y * 0.1f, -90.0f, 90.0f);
			_transform->set_local_euler_angles(ue::vector3::get_right() * _rotation_x);
		}

		if (ue::input::get_key(UE_KEY_W))
			_transform->translate(-_transform->get_forward() * ue::time::get_delta());
		else if (ue::input::get_key(UE_KEY_S))
			_transform->translate(_transform->get_forward() * ue::time::get_delta());
		if (ue::input::get_key(UE_KEY_D))
			_transform->translate(_transform->get_right() * ue::time::get_delta());
		else if (ue::input::get_key(UE_KEY_A))
			_transform->translate(-_transform->get_right() * ue::time::get_delta());
		if (ue::input::get_key(UE_KEY_E))
			_transform->translate(_transform->get_up() * ue::time::get_delta());
		else if (ue::input::get_key(UE_KEY_Q))
			_transform->translate(-_transform->get_up() * ue::time::get_delta());

		_camera->set_aspect(static_cast<float>(_game_window.get_rectangle().width) 
			/ static_cast<float>(_game_window.get_rectangle().height));

		_shader->bind();
		_texture->bind();
		_shader->set_vector3("u_LightPosition", ue::vector3(5.0f, 5.0f, 5.0f));
		_shader->set_vector3("u_ViewPosition", _transform->get_position());
		_shader->set_matrix4x4("u_ViewProjection", _camera->get_projection_matrix() * _transform->get_world_to_local());
		_vertex_array->bind();
		ue::gl::draw_elements(ue::gl::get_triangles_mode(), _index_buffer->get_count(), _index_buffer->get_type());

		_framebuffer->unbind();
	}

	void on_gui() override
	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 25.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::Begin("DockSpace", nullptr, window_flags);
		ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("DockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		// MenuBar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save", "Cntrl+S"))
				{
					// Saving
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();

		_scene_hierarchy_window.show();
		_game_window.show();
	}
};