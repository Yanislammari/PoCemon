#include <SDL.h>
#include "includes/screen.h"
#include "includes/game.h"

void run_game() {
    SDL_Window* window = SDL_CreateWindow("PoCemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Screen homeScreen = initializeScreen(renderer, "../assets/screen/home_screen.gif");
    enum GameState gameState = STATE_HOME;

    int quit = 0;
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = 1;
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_f) {
                    fullScreenWindow(window);
                }
            }
        }

        SDL_RenderClear(renderer);
        if(gameState == STATE_HOME) {
            displayScreen(renderer, &homeScreen);
        }
    }

    removeScreen(homeScreen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}