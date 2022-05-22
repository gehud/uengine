project "Core"
	kind "StaticLib"
	systemversion "latest"
	cppdialect "C++17"

	targetdir ("bin/" .. output_dir .. "/%{prj.name}")
	objdir ("bin/int/" .. output_dir .. "/%{prj.name}")

	files {
		"include/**.h",
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"include",
		"src",
		"dependencies/spdlog/include",
		"dependencies/glfw/include",
		"dependencies/glad/include",
		"dependencies/glm",
		"dependencies/stb"
	}

	links {
		"GLFW",
		"Glad"
	}

	defines {
		"GLFW_INCLUDE_NONE"
	}

	filter "system:windows"
		defines {
			"UE_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
			"UE_DEBUG"
		}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines {
			"UE_RELEASE"
		}
		runtime "Release"
		optimize "on"