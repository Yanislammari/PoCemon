#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WHITE_COLOR (SDL_Color) {255, 255, 255}
#define BLACK_COLOR (SDL_Color) {0, 0, 0}
#define BLUE_COLOR (SDL_Color) {0, 0, 255}

enum GameState {
    STATE_HOME,
    STATE_MENU,
    STATE_SAVELIST,
    STATE_GAME,
    STATE_BATTLE
};

void run_game();

#endif
