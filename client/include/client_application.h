#pragma once

#include <uengine/application.h>
#include <uengine/events.h>
#include <uengine/log.h>

#include <uengine/rendering/gl.h>
#include <uengine/rendering/vertex_array.h>
#include <uengine/rendering/vertex_buffer.h>
#include <uengine/rendering/index_buffer.h>
#include <uengine/rendering/texture_2d.h>
#include <uengine/rendering/shader.h>
#include <uengine/rendering/camera.h>

using namespace ue;

class client_application : public application
{
private:
	std::shared_ptr<vertex_array> _vertex_array;
	std::shared_ptr<vertex_buffer> _vertex_buffer;
	std::shared_ptr<index_buffer> _index_buffer;
	std::shared_ptr<texture_2d> _texture;
	std::shared_ptr<shader> _shader;
	camera _camera;
public:
	client_application() : _camera(16.0f / 9.0f)
	{
		_vertex_array = vertex_array::create();
		_vertex_array->bind();

		float vertices[4 * 5] = 
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
		};

		_vertex_buffer = vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float), sizeof(float));
		_vertex_buffer->set_layout({
			{ vertex_attribute_format::float3, "a_Position"},
			{ vertex_attribute_format::float2, "a_UV"}
		});

		unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };

		_index_buffer = index_buffer::create(indices, sizeof(indices) / sizeof(unsigned int), sizeof(unsigned int));

		_texture = texture_2d::create("assets/textures/checkerboard.png");
		_texture->set_filter_mode(texture_filter_mode::nearest);

		_shader = shader::create("assets/shaders/texture.glsl");
		_shader->set_int(0, "u_Texture");
	}

	void on_update() override 
	{
		gl::clear_color(0.1f, 0.1f, 0.1f, 1.0f);
		gl::clear();

		_camera.set_position({ 0.0f, 0.0f, -1.0f });
		_camera.set_rotation({ 15.0f, 15.0f, 0.0f });

		_shader->bind();
		_texture->bind();
		_shader->set_float4(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "u_Color");
		_shader->set_mat4(_camera.get_view_projection(), "u_ViewProjection");
		_vertex_array->bind();
		gl::draw_elements(gl::get_triangles_mode(), _index_buffer->get_count(), _index_buffer->get_type());
	}
};