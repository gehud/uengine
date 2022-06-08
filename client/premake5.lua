project "Client"
	kind "ConsoleApp"
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
		"../core/include",
		"../core/src",
		"../core/dependencies/spdlog/include",
		"../core/dependencies/glfw/include",
		"../core/dependencies/glad/include",
		"../core/dependencies/vulkan/include",
		"../core/dependencies/glm",
		"../core/dependencies/stb",
		"../core/dependencies/imgui",
		"../core/dependencies/entt/single_include",
		"../core/dependencies/assimp/include",
	}

	links {
		"Core"
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