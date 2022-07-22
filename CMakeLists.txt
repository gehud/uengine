cmake_minimum_required(VERSION 3.6)

project(uengine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

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
		GLFW_INCLUDE_NONE
		UE_PLATFORM_WINDOWS
)

add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/stb)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/entt)

list(APPEND INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/source
)

list(APPEND LIBS spdlog::spdlog glfw glad stb glm EnTT)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})