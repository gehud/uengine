project(Core VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(UE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(UE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})

configure_file(source/uengine/core/configuration.h.in source/uengine/core/configuration.h)

file(GLOB_RECURSE CORE_SOURCE_FILES 
	${PROJECT_SOURCE_DIR}/include/*.h
	${PROJECT_SOURCE_DIR}/source/*.h
	${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} STATIC ${CORE_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/source)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		_CRT_SECURE_NO_WARNINGS
	PUBLIC
		$<$<CONFIG:Debug>:UE_DEBUG>
		$<$<CONFIG:RelWithDebInfo>:UE_DEBUG>
		$<$<CONFIG:Release>:UE_RELEASE>
		$<$<CONFIG:MinSizeRel>:UE_RELEASE>)

list(APPEND GENERAL_INCLUDE_DIRECTORIES ${PROJECT_BINARY_DIR}/source)

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
	target_include_directories(${PROJECT_NAME} PUBLIC ${GENERAL_INCLUDE_DIRECTORIES})
	target_compile_definitions(${PROJECT_NAME} PUBLIC UE_WINDOWS)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL Android)
	add_library(app-glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
	target_link_libraries(${PROJECT_NAME} app-glue)

	if (${ANDROID_ABI} STREQUAL "x86_64")
		set(ANDROID_HEADER_TRIPPLE x86_64-linux-android)
	elseif (${ANDROID_ABI} STREQUAL "x86")
		set(ANDROID_HEADER_TRIPPLE i686-linux-android)
	elseif (${ANDROID_ABI} STREQUAL "arm64-v8a")
		set(ANDROID_HEADER_TRIPPLE aarch64-linux-android)
	elseif (${ANDROID_ABI} STREQUAL "armeabi-v7a")
		set(ANDROID_HEADER_TRIPPLE arm-linux-androideabi)
	endif()

	target_include_directories(${PROJECT_NAME}
		PUBLIC
			${GENERAL_INCLUDE_DIRECTORIES}
			${ANDROID_NDK}/sources/android/native_app_glue
			${ANDROID_SYSROOT}/usr/include
			${ANDROID_SYSROOT}/usr/include/${ANDROID_HEADER_TRIPPLE})

	target_compile_definitions(${PROJECT_NAME} PUBLIC UE_ANDROID)
endif()