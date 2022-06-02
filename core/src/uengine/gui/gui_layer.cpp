#include "gui_layer.h"

#include "uengine/core/application.h"

#include <imgui.h>
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

	static ImVec4 _active_main_color = ImVec4(0.36f, 0.21f, 0.62f, 1.0f);
	static ImVec4 _disabled_main_color = ImVec4(0.22f, 0.22f, 0.22f, 1.0f);
	static ImVec4 _window_background_color = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
	static ImVec4 _border_color = ImVec4(0.24f, 0.24f, 0.24f, 1.0f);

	static void set_style() 
	{
		ImGuiStyle dark_style;
		ImGui::StyleColorsDark(&dark_style);
		dark_style.WindowMinSize = ImVec2(128, 128);

		dark_style.Colors[ImGuiCol_WindowBg] = _window_background_color;
		dark_style.Colors[ImGuiCol_Border] = _border_color;

		dark_style.Colors[ImGuiCol_TitleBg] = _active_main_color;
		dark_style.Colors[ImGuiCol_TitleBgActive] = _active_main_color;
		dark_style.Colors[ImGuiCol_TitleBgCollapsed] = _active_main_color;

		dark_style.Colors[ImGuiCol_ResizeGripHovered] = _active_main_color;
		dark_style.Colors[ImGuiCol_ResizeGripActive] = _active_main_color;
		dark_style.Colors[ImGuiCol_ResizeGrip].w = 0.0f;

		dark_style.Colors[ImGuiCol_Separator] = _border_color;
		dark_style.Colors[ImGuiCol_SeparatorActive] = _active_main_color;
		dark_style.Colors[ImGuiCol_SeparatorHovered] = _active_main_color;

		dark_style.Colors[ImGuiCol_Tab] = _active_main_color;
		dark_style.Colors[ImGuiCol_TabActive] = _active_main_color;
		dark_style.Colors[ImGuiCol_TabHovered] = _active_main_color;
		dark_style.Colors[ImGuiCol_TabUnfocusedActive] = _active_main_color;
		dark_style.Colors[ImGuiCol_TabUnfocused] = _active_main_color;

		dark_style.Colors[ImGuiCol_Button] = _disabled_main_color;
		dark_style.Colors[ImGuiCol_ButtonActive] = _active_main_color;
		dark_style.Colors[ImGuiCol_ButtonHovered] = _active_main_color;


		dark_style.Colors[ImGuiCol_DockingPreview] = _active_main_color;

		ImGui::GetStyle() = dark_style;
	}
}