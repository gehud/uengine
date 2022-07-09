#include "uengine/core/entry_point.h"

class client_application : public ue::application {
public:
	client_application() {
	}
};

ue::application* ue::create_application() {
	return new client_application();
}