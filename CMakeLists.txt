cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 26)

project(seasons LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(seasons main.cpp game.cpp game.h
        Player.cpp
        Player.h
        Map.cpp
        Map.h)
target_compile_features(seasons PRIVATE cxx_std_17)
target_link_libraries(seasons PRIVATE SFML::Graphics)