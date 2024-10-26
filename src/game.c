#include <SDL.h>
#include "includes/screen.h"
#include "includes/game.h"

void run_game() {
    SDL_Window* window = SDL_CreateWindow("PoCemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Screen homeScreen = initialize_screen(renderer, "../assets/screen/home_screen.gif");
    enum GameState gameState = STATE_HOME;

    int quit = 0;
    SDL_Event e;
    Screen menuScreen;
    Screen savelist_screen;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = 1;
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_f) {
                    full_screen_window(window);
                }
                if(gameState == STATE_HOME) {
                    if(e.key.keysym.sym == SDLK_RETURN) {
                        remove_screen(homeScreen);
                        menuScreen = initialize_screen(renderer, "../assets/screen/menu_screen.gif");
                        gameState = STATE_MENU;
                    }
                }
                else if(gameState == STATE_MENU) {
                    if(e.key.keysym.sym == SDLK_RETURN) {
                        remove_screen(menuScreen);
                        savelist_screen = initialize_screen(renderer, "../assets/screen/savelist_screen.gif");
                        gameState = STATE_SAVELIST;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        if(gameState == STATE_HOME) {
            display_screen(renderer, &homeScreen);
        }
        else if(gameState == STATE_MENU) {
            display_screen(renderer, &menuScreen);
        }
    }

    remove_screen(homeScreen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
