cmake_minimum_required(VERSION 3.28.3)

project(Game)

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

add_executable(Game 
	src/main.cpp)

target_link_libraries(Game ${SDL3_LIBRARIES})
