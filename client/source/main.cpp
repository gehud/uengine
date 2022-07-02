#include "uengine/core/entry_point.h"

ue::application* ue::create_application() {
	return new ue::application();
}