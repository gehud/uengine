#pragma once

#include "mesh.h"
#include "uengine/core/window.h"
#include "uengine/core/assertion.h"

#include <glad/glad.h>

namespace ue {
	enum class graphics_api_type {
		opengl,
	};

	enum buffer_bits {
		color_buffer_bit = GL_COLOR_BUFFER_BIT,
		depth_buffer_bit = GL_DEPTH_BUFFER_BIT,
	};

	enum class draw_mode {
		triangles = GL_TRIANGLES,
	};

	class graphics final {
	public:
		graphics() = delete;

		static graphics_api_type get_api_type() { return _api_type; }

		static void initialize() {
			static bool is_graphics_initialized = false;

			if (is_graphics_initialized)
				return;

			UE_CORE_ASSERT(&window::get_instance(), "Missing window.");
			GLFWwindow* window = static_cast<GLFWwindow*>(window::get_instance().get_handle());
			glfwMakeContextCurrent(window);
			int gl_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			UE_CORE_ASSERT(gl_status, "Failed to initialize OpenGL.");

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);	

			is_graphics_initialized = true;
		}

		static void terminate() {
			glfwTerminate();
		}

		static void clear_color(float r, float g, float b, float a) { 
			glClearColor(r, g, b, a);
		}

		static void clear(int32 mask) {
			glClear(mask);
		}

		static void draw_elements(draw_mode mode, uint32 count, index_format format) {
			GLenum type = 0;
			switch (format) {
				case index_format::uint8: {
					type = GL_UNSIGNED_BYTE;
					break;
				}
				case index_format::uint16: {
					type = GL_UNSIGNED_SHORT;
					break;
				}
				case index_format::uint32: {
					type = GL_UNSIGNED_INT;
					break;
				}
			}
			glDrawElements(static_cast<GLenum>(mode), count, type, NULL);
		}

		static void draw_mesh(const reference<mesh>& mesh) {
			mesh->bind();
			draw_elements(draw_mode::triangles, mesh->get_index_buffer()->get_count(), mesh->get_index_format());
		}
	private:
		static graphics_api_type _api_type;
	};
}