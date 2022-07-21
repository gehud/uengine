#include <uengine/core/entry_point.h>
#include <uengine/core/window.h>
#include <uengine/math/vector2.h>
#include <uengine/math/vector3.h>
#include <uengine/math/matrix4x4.h>
#include <uengine/math/quaternion.h>
#include <uengine/core/input.h>
#include <uengine/core/keycodes.h>
#include <uengine/core/time.h>
#include <uengine/core/memory.h>

#include <uengine/rendering/mesh.h>
#include <uengine/rendering/shader.h>
#include <uengine/rendering/texture.h>
#include <uengine/rendering/graphics.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct vertex {
	ue::vector3 position;
	ue::vector3 normal;
	ue::vector2 uv;

	vertex(const ue::vector3& position, const ue::vector3& normal, const ue::vector2& uv)
		: position(position), normal(normal), uv(uv) { }
};

class client_application : public ue::application {
public:
	client_application() {
		ue::window::get_instance().set_vsync(true);

		vertex vertices[24] = {
			{ { -0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f }, { 0.0f,  0.0f } },
			{ { -0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f }, { 0.0f,  1.0f } },
			{ {  0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f }, { 1.0f,  1.0f } },
			{ {  0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f }, { 1.0f,  0.0f } },

			{ {  0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 0.0f,  0.0f } },
			{ {  0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 0.0f,  1.0f } },
			{ { -0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 1.0f,  1.0f } },
			{ { -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 1.0f,  0.0f } },

			{ {  0.5f, -0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f }, { 0.0f,  0.0f } },
			{ {  0.5f,  0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f }, { 0.0f,  1.0f } },
			{ {  0.5f,  0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f }, { 1.0f,  1.0f } },
			{ {  0.5f, -0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f }, { 1.0f,  0.0f } },

			{ { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f,  0.0f }, { 0.0f,  0.0f } },
			{ { -0.5f,  0.5f, -0.5f }, { -1.0f, 0.0f,  0.0f }, { 0.0f,  1.0f } },
			{ { -0.5f,  0.5f,  0.5f }, { -1.0f, 0.0f,  0.0f }, { 1.0f,  1.0f } },
			{ { -0.5f, -0.5f,  0.5f }, { -1.0f, 0.0f,  0.0f }, { 1.0f,  0.0f } },

			{ { -0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f }, { 0.0f,  0.0f } },
			{ { -0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f }, { 0.0f,  1.0f } },
			{ {  0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f }, { 1.0f,  1.0f } },
			{ {  0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f }, { 1.0f,  0.0f } },

			{ {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f,  0.0f } },
			{ {  0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f,  1.0f } },
			{ { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f,  1.0f } },
			{ { -0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f,  0.0f } }
		};

		ue::uint32 indices[36] = {
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,
			16, 17, 18, 16, 18, 19,
			20, 21, 22, 20, 22, 23,
		};

		_mesh = ue::mesh::create();

		_mesh->set_vertex_buffer_params(sizeof(vertices) / sizeof(vertex), {
			{ "a_Position", ue::vertex_attribute_format::float32, 3 },
			{ "a_Normal", ue::vertex_attribute_format::float32, 3 },
			{ "a_UV", ue::vertex_attribute_format::float32, 2 }
		});
		_mesh->set_vertex_buffer_data(vertices);

		_mesh->set_index_buffer_params(sizeof(indices) / sizeof(ue::uint32));
		_mesh->set_index_buffer_data(indices);

		_shader = ue::shader::create("C:/Development/UEngine/client/assets/shaders/texture.glsl");
		_shader->set_int("u_Texture", 0);

		_texture = ue::texture2d::create("C:/Development/UEngine/client/assets/textures/checkerboard.png");
		_texture->set_filter_mode(ue::texture_filter_mode::nearest);
	}

	void update() {
		ue::graphics::clear_color(0.1f, 0.1f, 0.1f, 1.0f);
		ue::graphics::clear(ue::color_buffer_bit | ue::depth_buffer_bit);

		_shader->bind();
		_texture->bind();
		_shader->set_vector3("u_LightPosition", ue::vector3(5.0f, 5.0f, 5.0f));
		_shader->set_vector3("u_ViewPosition", ue::vector3(0, 2, 0));
		_shader->set_matrix4x4("u_Transform", ue::quaternion(ue::vector3(0, ue::time::get_time(), 0)));
		_shader->set_matrix4x4("u_ViewProjection", ue::matrix4x4::perspective(60.0f, 1.9f, 0.01f, 500.0f) * ue::matrix4x4::translate(0.0f, 0.0f, -2.0f));
		_shader->set_vector4("u_Color", ue::vector4(1.0f, 0.0f, 0.0f, 1.0f));
		ue::graphics::draw_mesh(_mesh);
	}
private:
	ue::reference<ue::mesh> _mesh;
	ue::reference<ue::shader> _shader;
	ue::reference<ue::texture> _texture;
};

ue::application* ue::create_application() {
	return new client_application();
}