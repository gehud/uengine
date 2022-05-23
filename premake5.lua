workspace "UEngine"
	configurations {
		"Debug",
		"Release"
	}
	architecture "x64"
	language "C++"
	startproject "Editor"

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "core"
include "editor"
include "client"
group "Dependencies"
	include "core/dependencies/glfw"
	include "core/dependencies/glad"
	include "core/dependencies/imgui"