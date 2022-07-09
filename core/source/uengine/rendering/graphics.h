#pragma once

#include "graphics_api.h"

namespace ue {
	enum class graphics_api_type {
		opengl
	};

	class graphics final {
	public:
		static void initialize();
		static void terminate();

		static graphics_api_type get_api_type() { return _api_type; }
	private:
		static graphics_api_type _api_type;
		static graphics_api* _api;
	};
}