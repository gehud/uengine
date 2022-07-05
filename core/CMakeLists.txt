project(core VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(UE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(UE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(UE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

configure_file(source/uengine/core/configuration.h.in source/uengine/core/configuration.h)

file(GLOB_RECURSE CORE_SOURCE_FILES 
	${PROJECT_SOURCE_DIR}/include/*.h
	${PROJECT_SOURCE_DIR}/source/*.h
	${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} STATIC ${CORE_SOURCE_FILES})

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		_CRT_SECURE_NO_WARNINGS
	PUBLIC
		$<$<CONFIG:Debug>:UE_DEBUG>
		$<$<CONFIG:RelWithDebInfo>:UE_DEBUG>
		$<$<CONFIG:Release>:UE_RELEASE>
		$<$<CONFIG:MinSizeRel>:UE_RELEASE>)

add_subdirectory(dependencies/spdlog)

set(UE_WINDOWS FALSE)
set(UE_ANDROID FALSE)

if(WIN32)
	set(UE_WINDOWS TRUE)
elseif(ANDROID)
	set(UE_ANDROID TRUE)
endif()

list(APPEND INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/source
	${PROJECT_BINARY_DIR}/source)

list(APPEND LIBS spdlog::spdlog)

if(UE_WINDOWS)
	target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
	target_compile_definitions(${PROJECT_NAME} PUBLIC UE_WINDOWS)
	target_link_libraries(${PROJECT_NAME} ${LIBS})
elseif(UE_ANDROID)
	add_library(Glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
	target_link_libraries(${PROJECT_NAME} ${LIBS} Glue)
	target_include_directories(${PROJECT_NAME}
		PUBLIC
			${INCLUDE_DIRS}
			${ANDROID_NDK}/sources/android/native_app_glue
			${CMAKE_SYSROOT}/usr/include
			${CMAKE_SYSROOT}/usr/include/${ANDROID_ARCH})

	target_compile_definitions(${PROJECT_NAME} PUBLIC UE_ANDROID)
endif()