#include <uengine/core/entry_point.h>
#include <uengine/core/window.h>
#include <uengine/math/vector2.h>
#include <uengine/core/input.h>

#include <glad/glad.h>

class client_application : public ue::application {
public:
	client_application() {
		ue::window::get_instance().set_vsync(true);
	}

	void update() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
};

ue::application* ue::create_application() {
	return new client_application();
}