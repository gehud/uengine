project "Editor"
	kind "ConsoleApp"
	language "C++"

	objdir ("build/obj/%{cfg.buildcfg}-%{cfg.platform}")
	targetdir ("build/%{cfg.buildcfg}-%{cfg.platform}")

	files {
		"include/**.h",
		"source/**.h",
		"source/**.cpp",
	}

	includedirs {
		"include",
		"source",
		"../core/include",
		"../core/source",
		"../core/dependencies/spdlog/include",
		"../core/dependencies/glfw/include",
		"../core/dependencies/glad/include",
		"../core/dependencies/vulkan/include",
		"../core/dependencies/glm",
		"../core/dependencies/stb",
		"../core/dependencies/imgui",
		"../core/dependencies/entt/src",
	}

	links {
		"Core"
	}

    filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		defines {
			"UE_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
			"UE_DEBUG"
		}
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines {
			"UE_RELEASE"
		}
		runtime "Release"
		optimize "On"

	filter "platforms:Windows32"
		architecture "x86"

	filter "platforms:Windows64"
		architecture "x86_64"