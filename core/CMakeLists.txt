cmake_minimum_required(VERSION 3.6)

project(core VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(UE_VERSION ${PROJECT_VERSION})
set(UE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(UE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(UE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

configure_file(source/uengine/core/configuration.h.in source/uengine/core/configuration.h)

file(GLOB_RECURSE UE_SOURCE_FILES 
	${PROJECT_SOURCE_DIR}/include/*.h
	${PROJECT_SOURCE_DIR}/source/*.h
	${PROJECT_SOURCE_DIR}/source/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${UE_SOURCE_FILES})

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		_CRT_SECURE_NO_WARNINGS
	PUBLIC
		$<$<CONFIG:Debug>:UE_DEBUG>
		$<$<CONFIG:RelWithDebInfo>:UE_DEBUG>
		$<$<CONFIG:Release>:UE_RELEASE>
		$<$<CONFIG:MinSizeRel>:UE_RELEASE>
		UE_PLATFORM_WINDOWS
		GLFW_INCLUDE_NONE
)

add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/stb)
add_subdirectory(dependencies/glm)

list(APPEND INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/source
	${PROJECT_BINARY_DIR}/source
)

list(APPEND LIBS spdlog::spdlog glfw glad stb glm)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})