cmake_minimum_required(VERSION 3.0)
project(Ukol_4)

# Přidání hlavního spustitelného souboru
add_executable(advent_lod ${CMAKE_CURRENT_SOURCE_DIR}/advent_lod.cpp)

# Nastavení adresáře pro sestavení jako podadresář projektu
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# Přidání spustitelného souboru pro testy
add_executable(mytests ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

# Nalezení Google Test frameworku
enable_testing()
find_package(GTest REQUIRED)
# Připojení Google Testu k testům
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(mytests GTest::gtest_main pthread) 

# Definování __TEST__ pro testovací kompilaci
target_compile_definitions(mytests PRIVATE __TEST__)

# Registrace testu
add_test(NAME mytests COMMAND mytests)

# Kopírování vstupních souborů do adresáře build po sestavení cíle mytests
add_custom_command(TARGET mytests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/advent_lod/vstup_1.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/vstup_1.txt")

add_custom_command(TARGET mytests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/advent_lod/vstup_2.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/vstup_2.txt")

add_custom_command(TARGET mytests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/advent_lod/vstup_3.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/vstup_3.txt")
