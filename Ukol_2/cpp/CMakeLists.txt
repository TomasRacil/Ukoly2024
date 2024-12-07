cmake_minimum_required(VERSION 3.10)
project(Ukol_2)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(${GTEST_INCLUDE_DIRS})

# Add the executable
add_executable(sifry src/sifry.cpp)

# Find and link GTest
find_package(GTest REQUIRED)
target_link_libraries(sifry GTest::GTest GTest::Main)
