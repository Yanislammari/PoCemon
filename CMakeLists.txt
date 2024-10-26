cmake_minimum_required(VERSION 3.26)
project(pocemon C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(GIF REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${GIF_INCLUDE_DIRS} /usr/local/include)

find_library(SDL2_MIXER_LIB NAMES SDL2_mixer PATHS /opt/homebrew/lib)
if(NOT SDL2_MIXER_LIB)
    message(FATAL_ERROR "SDL2_mixer library not found")
endif()

add_executable(pocemon
        main.c
        src/game.c
        src/includes/game.h
        src/screen.c
        src/includes/screen.h
        src/gif.c
        src/includes/gif.h
        src/text.c
        src/includes/text.h
        src/map.c
        src/includes/map.h
)

find_library(TMX_LIB NAMES tmx PATHS /usr/local/lib)
if(NOT TMX_LIB)
    message(FATAL_ERROR "tmx library not found")
endif()

target_link_libraries(pocemon ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIB} ${GIF_LIBRARIES} ${TMX_LIB})
