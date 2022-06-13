cmake_minimum_required(VERSION 3.10)

project(Core LANGUAGES CXX)

file(GLOB_RECURSE CORE_FILES 
	${PROJECT_SOURCE_DIR}/include/*.h
	${PROJECT_SOURCE_DIR}/source/*.h
	${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(Core STATIC ${CORE_FILES})

target_include_directories(Core PRIVATE
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/source)