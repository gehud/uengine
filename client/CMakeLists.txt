project(client LANGUAGES CXX)

file(GLOB_RECURSE CLIENT_SOURCE_FILES 
	${PROJECT_SOURCE_DIR}/include/*.h
	${PROJECT_SOURCE_DIR}/source/*.h
	${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${CLIENT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} 
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/source)

target_link_libraries(${PROJECT_NAME} core)