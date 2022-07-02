project(Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CLIENT_SOURCE_FILES 
	${PROJECT_SOURCE_DIR}/include/*.h
	${PROJECT_SOURCE_DIR}/source/*.h
	${PROJECT_SOURCE_DIR}/source/*.cpp)

if(${CMAKE_SYSTEM_NAME} STREQUAL Android)
	add_library(Client STATIC ${CLIENT_SOURCE_FILES})
else()
	add_executable(Client ${CLIENT_SOURCE_FILES})
endif()

target_include_directories(Client PRIVATE
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/source)

target_link_libraries(Client Core)