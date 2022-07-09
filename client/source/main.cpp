#include <uengine/core/entry_point.h>
#include <uengine/core/window.h>

class client_application : public ue::application {
public:
	client_application() {
		ue::window::get_instance().set_vsync(true);
	}
};

ue::application* ue::create_application() {
	return new client_application();
}