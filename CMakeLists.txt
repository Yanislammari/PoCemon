cmake_minimum_required(VERSION 3.26)
project(pocemon C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(SDL2_PATH "/Users/yanislammari/Documents/SDL2-2.30.1/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} /usr/local/include)

find_library(SDL2_MIXER_LIB NAMES SDL2_mixer PATHS /opt/homebrew/lib)
if(NOT SDL2_MIXER_LIB)
    message(FATAL_ERROR "SDL2_mixer library not found")
endif()

add_executable(pocemon
        main.c
        src/game.c
        src/includes/game.h
)

target_link_libraries(pocemon ${SDL2_LIBRARY})