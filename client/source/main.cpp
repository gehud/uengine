#include "uengine/core/entry_point.h"
#include "uengine/core/configuration.h"
#include "uengine/core/assertion.h"

#include <iostream>

class client_application : public ue::application {
public:
	client_application() {

	}
};

ue::application* ue::create_application() {
	return new client_application();
}