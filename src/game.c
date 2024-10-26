#include <SDL.h>
#include "includes/screen.h"
#include "includes/game.h"

void run_game() {
    SDL_Window* window = SDL_CreateWindow("PoCemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Screen home_screen = initialize_screen(renderer, "../assets/screen/home_screen.gif");
    enum GameState game_state = STATE_HOME;

    int quit = 0;
    SDL_Event e;
    Screen menu_screen;
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
                if(game_state == STATE_HOME) {
                    if(e.key.keysym.sym == SDLK_RETURN) {
                        remove_screen(home_screen);
                        menu_screen = initialize_screen(renderer, "../assets/screen/menu_screen.gif");
                        game_state = STATE_MENU;
                    }
                }
                else if(game_state == STATE_MENU) {
                    if(e.key.keysym.sym == SDLK_RETURN) {
                        remove_screen(menu_screen);
                        savelist_screen = initialize_screen(renderer, "../assets/screen/savelist_screen.gif");
                        game_state = STATE_SAVELIST;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        if(game_state == STATE_HOME) {
            display_screen(renderer, &home_screen);
        }
        else if(game_state == STATE_MENU) {
            display_screen(renderer, &menu_screen);
        }
    }

    remove_screen(home_screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
