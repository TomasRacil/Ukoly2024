cmake_minimum_required(VERSION 3.0)
project(Ukol_5)

set (CMAKE_CXX_STANDARD 11)

# Add your main executable
add_executable(ukol5 source.cpp
        organisumus.cpp
        rostlina.cpp
        zvire.cpp
        masozravec.cpp
        bylozravec.cpp)

# Set the build directory to be a subdirectory of the project directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
