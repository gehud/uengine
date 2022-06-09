project "Core"
	kind "StaticLib"
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
		"dependencies/spdlog/include",
		"dependencies/glfw/include",
		"dependencies/glad/include",
		"dependencies/vulkan/include",
		"dependencies/glm",
		"dependencies/stb",
		"dependencies/imgui",
		"dependencies/entt/src",
		"dependencies/assimp/include",
	}

	links {
		"GLFW",
		"Glad",
		"Vulkan",
		"ImGui",
		"Assimp",
	}

	defines {
		"GLFW_INCLUDE_NONE",
		"GLFW_INCLUDE_VULKAN",
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		defines {
			"UE_WINDOWS",
			"GLFW_EXPOSE_NATIVE_WIN32",
			"VK_USE_PLATFORM_WIN32_KHR",
			"_CRT_SECURE_NO_WARNINGS",
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