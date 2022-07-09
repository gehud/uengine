#include "uengine/core/entry_point.h"
#include "uengine/core/log.h"

class client_application : public ue::application {
public:
	client_application() {
		UE_LOG_INFO("Test");
	}
};

ue::application* ue::create_application() {
	return new client_application();
}