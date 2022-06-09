workspace "UEngine"
	configurations { "Debug", "Release" }
	platforms { "Windows32", "Windows64" }
	startproject "Client"

include "core"
include "editor"
include "client"
group "Dependencies"
	include "core/dependencies/glfw"
	include "core/dependencies/glad"
	include "core/dependencies/vulkan"
	include "core/dependencies/imgui"
	include "core/dependencies/assimp"