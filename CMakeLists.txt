cmake_minimum_required(VERSION 3.26)
project(pocemon C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(GIF REQUIRED)
find_package(SQLite3 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${GIF_INCLUDE_DIRS} /usr/local/include)

find_library(SDL2_MIXER_LIB NAMES SDL2_mixer PATHS /opt/homebrew/lib)
find_library(TMX_LIB NAMES tmx PATHS /usr/local/lib)

add_executable(
        pocemon
        main.c
        src/screen.c
        src/game.c
        src/includes/game.h
        src/includes/screen.h
        src/text.c
        src/includes/text.h
        src/gif.c
        src/includes/gif.h
        src/map.c
        src/includes/map.h
        src/character.c
        src/includes/character.h
        src/database.c
        src/includes/database.h
        src/pokemon.c
        src/includes/pokemon.h
)

target_link_libraries(pocemon ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIB} ${GIF_LIBRARIES} ${TMX_LIB} SQLite::SQLite3)