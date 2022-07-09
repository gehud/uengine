project(glad LANGUAGES C)

add_library(${PROJECT_NAME} STATIC src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC "include")