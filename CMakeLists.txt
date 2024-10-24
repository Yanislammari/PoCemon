cmake_minimum_required(VERSION 3.26)
project(pocemon C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_executable(pocemon
        main.c
)
