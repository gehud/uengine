cmake_minimum_required(VERSION 3.10)

project(Client LANGUAGES CXX)

file(GLOB_RECURSE CLIENT_FILES 
	${PROJECT_SOURCE_DIR}/include/*.h
	${PROJECT_SOURCE_DIR}/source/*.h
	${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(Client ${CLIENT_FILES})

target_include_directories(Client PRIVATE
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/source
	${PROJECT_SOURCE_DIR}/../core/include)

target_link_libraries(Client Core)