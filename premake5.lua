workspace "UEngine"
	configurations {
		"Debug",
		"Release"
	}
	architecture "x64"
	language "C++"
	startproject "Client"

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "core"
include "client"
group "Dependencies"
	include "core/dependencies/glfw"