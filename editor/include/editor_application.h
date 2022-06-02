#pragma once

#include <uengine.h>

#include <imgui.h>
#include <imgui_internal.h>

class editor_application : public ue::application
{
private:
	std::shared_ptr<ue::vertex_array> _vertex_array;
	std::shared_ptr<ue::vertex_buffer> _vertex_buffer;
	std::shared_ptr<ue::index_buffer> _index_buffer;
	std::shared_ptr<ue::frame_buffer> _frame_buffer;
	std::shared_ptr<ue::texture_2d> _texture;
	std::shared_ptr<ue::shader> _shader;
	int _game_window_width = 1280;
	int _game_window_height = 720;
	int _game_window_pos_x = 0;
	int _game_window_pos_y = 0;
	ue::scene _scene;
	ue::entity _entity;
	ue::transform* _transform;
	ue::camera* _camera;
	float _rotation_x = 0.0f;
public:
	editor_application()
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
		_shader->set_int(0, "u_Texture");

		_entity = ue::entity(_scene);
		_transform = &_entity.get_component<ue::transform>();
		_camera = &_entity.add_component<ue::camera>();
		_camera->set_aspect(16.0f / 9.0f);
		_transform->set_position({ 0.0f, 0.0f, 1.0f });
		add_scene(_scene);

		_frame_buffer = ue::frame_buffer::create({ 1280, 720 });
	}

	void on_update() override
	{
		_frame_buffer->bind();

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

		_shader->bind();
		_texture->bind();
		_shader->set_vector3(ue::vector3(5.0f, 5.0f, 5.0f), "u_LightPosition");
		_shader->set_vector3(_transform->get_position(), "u_ViewPosition");
		_shader->set_matrix4x4(_camera->get_projection_matrix() * _transform->get_world_to_local(), "u_ViewProjection");
		_vertex_array->bind();
		ue::gl::draw_elements(ue::gl::get_triangles_mode(), _index_buffer->get_count(), _index_buffer->get_type());

		_frame_buffer->unbind();
	}

	void on_gui() override
	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 25.0f));
		ImGui::Begin("DockSpace", nullptr, window_flags);
		ImGui::PopStyleVar(3);

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

		ImGui::Begin("Hierarchy");
		ImGui::Text("Hierarchy");
		ImGui::End();

		ImGui::Begin("Game");
		ImVec2 viewport_size = ImGui::GetWindowSize();
		_game_window_width = viewport_size.x;
		_game_window_height = viewport_size.y;
		ImGui::Image(reinterpret_cast<void*>(_frame_buffer->get_color_buffer_id()),
			ImVec2(_game_window_width, _game_window_height), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	}
};