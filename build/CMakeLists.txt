cmake_minimum_required(VERSION 3.28.3)

project(Game)

add_subdirectory(sdl EXCLUDE_FROM_ALL)
add_subdirectory(sdl_image EXCLUDE_FROM_ALL)

include_directories(../include)

add_executable(Game 
	../src/main.cpp
	../src/core.cpp
	../src/texture.cpp)

target_link_libraries(Game PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
