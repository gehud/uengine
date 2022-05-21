project "client"
	kind "ConsoleApp"
	systemversion "latest"
	cppdialect "C++17"

	targetdir ("bin/" .. output_dir .. "/%{prj.name}")
	objdir ("bin/int" .. output_dir .. "/%{prj.name}")

	files {
		"include/**.h",
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"include",
		"src",
		"../core/include",
	}

	links {
		"core"
	}

    filter "system:windows"
		defines {
			"UE_WINDOWS"
		}

	filter "configurations:debug"
		defines {
			"UE_DEBUG"
		}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:release"
		defines {
			"UE_RELEASE"
		}
		runtime "Release"
		optimize "on"