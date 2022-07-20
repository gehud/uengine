cmake_minimum_required(VERSION 3.6)

project(uengine)

add_subdirectory(core)
add_subdirectory(client)

set(VS_STARTUP_PROJECT client)