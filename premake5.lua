workspace "uengine"
	configurations {
		"debug",
		"release"
	}
	architecture "x64"
	language "C++"
	startproject "client"

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "core"
include "client"