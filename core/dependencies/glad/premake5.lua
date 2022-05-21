project "Glad"
	kind "StaticLib"
	systemversion "latest"
	language "C"

	targetdir ("bin/" .. output_dir .. "/%{prj.name}")
	objdir ("bin/int/" .. output_dir .. "/%{prj.name}")

	files {
		"include/**.h",
		"src/**.c"
	}

	includedirs {
		"include",
		"src"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"