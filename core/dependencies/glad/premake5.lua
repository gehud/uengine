project "Glad"
	kind "StaticLib"
	language "C"

	objdir ("build/obj/%{cfg.buildcfg}-%{cfg.platform}")
	targetdir ("build/%{cfg.buildcfg}-%{cfg.platform}")

	files {
		"include/**.h",
		"src/**.c",
	}

	includedirs {
		"include",
		"src",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "platforms:Windows32"
		architecture "x86"

	filter "platforms:Windows64"
		architecture "x86_64"