cmake_minimum_required(VERSION 3.0)
project(Ukol_5)



# Add your main executable
add_executable(advent_lod ${CMAKE_CURRENT_SOURCE_DIR}/source.cpp)

# Set the build directory to be a subdirectory of the project directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
