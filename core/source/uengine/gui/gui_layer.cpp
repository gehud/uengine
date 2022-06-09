#include "gui_layer.h"

#include "uengine/core/application.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_glfw.cpp>

#include <GLFW/glfw3.h>

namespace ue 
{
	void set_style();

	void gui_layer::on_attach()
	{
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		io.Fonts->AddFontFromFileTTF("../core/assets/fonts/open_sans/OpenSans-Bold.ttf", 22.0f);	
		io.FontDefault = io.Fonts->AddFontFromFileTTF("../core/assets/fonts/open_sans/OpenSans-Regular.ttf", 22.0f);

		set_style();
		application& app = application::get_instance();
		window& window = app.get_window();
		GLFWwindow* glfw_window = static_cast<GLFWwindow*>(window.get_native_window());
		ImGui_ImplOpenGL3_Init("#version 410");
		ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
	}

	void gui_layer::on_detach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void gui_layer::begin()
	{
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	}

	void gui_layer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		application& app = application::get_instance();
		io.DisplaySize = ImVec2(app.get_window().get_width(), app.get_window().get_height());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_context);
		}
	}

	// Style.

	static ImVec4 _text_color = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	static ImVec4 _disabled_text_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	static ImVec4 _active_color = ImVec4(0.36f, 0.21f, 0.62f, 1.0f);
	static ImVec4 _disabled_color = ImVec4(0.22f, 0.22f, 0.22f, 1.0f);
	static ImVec4 _background_color = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
	static ImVec4 _child_background_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	static ImVec4 _border_color = ImVec4(0.24f, 0.24f, 0.24f, 1.0f);

	static void set_style() 
	{
		ImGuiStyle dark_style;
		dark_style.WindowMinSize = ImVec2(128, 128);
		ImVec4* colors = dark_style.Colors;

		colors[ImGuiCol_Text] = _text_color;
		colors[ImGuiCol_TextDisabled] = _disabled_text_color;

		colors[ImGuiCol_WindowBg] = _background_color;
		colors[ImGuiCol_ChildBg] = _child_background_color;

		colors[ImGuiCol_PopupBg] = _background_color;

		colors[ImGuiCol_Border] = _border_color;
		colors[ImGuiCol_BorderShadow] = _border_color;

		colors[ImGuiCol_FrameBg] = _disabled_color;
		colors[ImGuiCol_FrameBgHovered] = _disabled_color;
		colors[ImGuiCol_FrameBgActive] = _disabled_color;

		colors[ImGuiCol_TitleBg] = _disabled_color;
		colors[ImGuiCol_TitleBgActive] = _disabled_color;
		colors[ImGuiCol_TitleBgCollapsed] = _disabled_color;

		colors[ImGuiCol_MenuBarBg] = _disabled_color;

		colors[ImGuiCol_ScrollbarBg] = _background_color;
		colors[ImGuiCol_ScrollbarGrab] = _background_color;
		colors[ImGuiCol_ScrollbarGrabHovered] = _background_color;
		colors[ImGuiCol_ScrollbarGrabActive] = _background_color;

		colors[ImGuiCol_CheckMark] = _active_color;

		colors[ImGuiCol_SliderGrab] = _active_color;
		colors[ImGuiCol_SliderGrabActive] = _active_color;

		colors[ImGuiCol_Button] = _background_color;
		colors[ImGuiCol_ButtonHovered] = _active_color;
		colors[ImGuiCol_ButtonActive] = colors[ImGuiCol_ButtonHovered];

		colors[ImGuiCol_Header] = _active_color;
		colors[ImGuiCol_HeaderHovered] = _active_color;
		colors[ImGuiCol_HeaderActive] = _active_color;

		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = _active_color;
		colors[ImGuiCol_SeparatorActive] = _active_color;

		colors[ImGuiCol_ResizeGrip] = _active_color;
		colors[ImGuiCol_ResizeGrip].w = 0.0f;
		colors[ImGuiCol_ResizeGripHovered] = _active_color;
		colors[ImGuiCol_ResizeGripActive] = _active_color;

		colors[ImGuiCol_Tab] = _disabled_color;
		colors[ImGuiCol_TabHovered] = _active_color;
		colors[ImGuiCol_TabActive] = _disabled_color;
		colors[ImGuiCol_TabUnfocused] = _disabled_color;
		colors[ImGuiCol_TabUnfocusedActive] = _disabled_color;

		colors[ImGuiCol_DockingPreview] = colors[ImGuiCol_HeaderActive];
		colors[ImGuiCol_DockingEmptyBg] = _background_color;

		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		dark_style.TabRounding = 0.0f;

		ImGui::GetStyle() = dark_style;
	}
}