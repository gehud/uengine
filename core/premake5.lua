project "Core"
	kind "StaticLib"
	systemversion "latest"
	cppdialect "C++17"

	targetname "uengine"

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
		"dependencies/vulkan/include",
		"dependencies/glm",
		"dependencies/stb",
		"dependencies/imgui",
		"dependencies/entt/single_include",
	}

	libdirs {
		"dependencies/vulkan/lib"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"Assimp",
		"vulkan-1.lib"
	}

	defines {
		"GLFW_INCLUDE_NONE",
		"GLFW_INCLUDE_VULKAN"
	}

	filter "system:windows"
		defines {
			"UE_WINDOWS",
			"GLFW_EXPOSE_NATIVE_WIN32",
			"VK_USE_PLATFORM_WIN32_KHR",
			"_CRT_SECURE_NO_WARNINGS"
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