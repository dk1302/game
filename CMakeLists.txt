cmake_minimum_required(VERSION 3.28.3)

project(Game)

add_subdirectory(sdl EXCLUDE_FROM_ALL)

add_executable(Game 
	src/main.cpp)

target_link_libraries(Game PRIVATE SDL3::SDL3)
