#pragma once

#include <uengine.h>

#include <imgui.h>
#include <imgui_internal.h>

class editor_camera_component : public ue::component
{
public:
	editor_camera_component(ue::entity& entity) : component(entity) { }
};

class editor_camera_system : public ue::system 
{

};

class editor_application : public ue::application
{
private:
	std::shared_ptr<ue::vertex_array> _vertex_array;
	std::shared_ptr<ue::vertex_buffer> _z_vertex_buffer;
	std::shared_ptr<ue::index_buffer> _index_buffer;
	std::shared_ptr<ue::frame_buffer> _frame_buffer;
	std::shared_ptr<ue::texture_2d> _texture;
	std::shared_ptr<ue::shader> _shader;
	float _mouse_sensitivity = 0.1f;
	int _game_window_width = 1280;
	int _game_window_height = 720;
	int _game_window_pos_x = 0;
	int _game_window_pos_y = 0;
	ue::scene _scene;
	ue::entity _editor_camera;
public:
	editor_application()
	{
		_vertex_array = ue::vertex_array::create();
		_vertex_array->bind();

		float vertices[4 * 5] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
		};

		_z_vertex_buffer = ue::vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float), sizeof(float));
		_z_vertex_buffer->set_layout({
			{ ue::vertex_attribute_format::float3, "a_Position"},
			{ ue::vertex_attribute_format::float2, "a_UV"}
			});

		unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };

		_index_buffer = ue::index_buffer::create(indices, sizeof(indices) / sizeof(unsigned int), sizeof(unsigned int));

		_frame_buffer = ue::frame_buffer::create(ue::frame_buffer_descriptor(1280, 720));

		_texture = ue::texture_2d::create("assets/textures/checkerboard.png");
		_texture->set_filter_mode(ue::texture_filter_mode::nearest);

		_shader = ue::shader::create("assets/shaders/texture.glsl");
		_shader->set_int(0, "u_Texture");

		ue::application::get_instance().get_window().on_resize += new ue::lambda<void, int, int>([](int width, int height)
		{
			ue::gl::viewport(0, 0, width, height);
		});

		add_scene(_scene);
		_editor_camera = ue::entity(_scene);
		_editor_camera.add_component<editor_camera_component>();
		add_system<editor_camera_system>();
	}

	void on_update() override
	{
		_frame_buffer->bind();

		ue::gl::clear_color(0.1f, 0.1f, 0.1f, 1.0f);
		ue::gl::clear();

		_shader->bind();
		_texture->bind();
		_shader->set_vector4(ue::vector4(1.0f, 0.0f, 0.0f, 1.0f), "u_Color");
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