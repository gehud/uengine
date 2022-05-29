#pragma once

#include "uengine/rendering/graphics_api.h"

struct VkInstance_T;

namespace ue 
{
	class vulkan_graphics_api : public graphics_api
	{
	private:
		VkInstance_T* _instance;
	public:
		~vulkan_graphics_api();

		void init() override;

		void clear_color(float r, float g, float b, float a) override {}

		void clear() override {}

		int get_triangles_mode() override { return -1; }

		void draw_elements(int mode, int count, int type) override {}

		void viewport(int x, int y, int width, int height) override {}
	};
}