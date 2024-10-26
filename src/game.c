#include <SDL.h>
#include <SDL_ttf.h>
#include "includes/screen.h"
#include "includes/game.h"
#include "includes/text.h"

void run_game() {
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("PoCemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("../assets/font/Daydream.ttf", 24);

    Screen home_screen = initialize_screen(renderer, "../assets/screen/home_screen.gif");
    enum GameState game_state = STATE_HOME;

    int quit = 0;
    SDL_Event e;
    Screen menu_screen;
    Screen savelist_screen;
    int menu_selected_option = 0;
    SDL_Color WHITE_COLOR = {255, 255, 255};
    SDL_Color BLACK_COLOR = {0, 0, 0};
    SDL_Color BLUE_COLOR = {0, 0, 255};
    SDL_Texture* map_texture = NULL;

    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;

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
                        if(menu_selected_option == 1) {
                            remove_screen(menu_screen);
                            savelist_screen = initialize_screen(renderer, "../assets/screen/menu_screen.gif");
                            game_state = STATE_SAVELIST;
                        }
                        else if(menu_selected_option == 0) {
                            remove_screen(menu_screen);
                            game_state = STATE_GAME;
                        }
                    }
                    else if(e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP) {
                        menu_selected_option = 1 - menu_selected_option;
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
            int textWidth;
            int textHeight;
            TTF_SizeText(font, "Nouvelle partie", &textWidth, &textHeight);
            int new_game_option_position_x = (WINDOW_WIDTH - textWidth) / 2;
            int load_game_option_position_x = (WINDOW_WIDTH - textWidth) / 2;
            int new_game_option_position_y = (WINDOW_HEIGHT - 2 * textHeight) / 2;
            int load_game_option_position_y = new_game_option_position_y + textHeight + 20;
            render_text(renderer, font, "Nouvelle partie", menu_selected_option == 0 ? BLUE_COLOR : WHITE_COLOR, new_game_option_position_x, new_game_option_position_y);
            render_text(renderer, font, "Charger Partie", menu_selected_option == 1 ? BLUE_COLOR : WHITE_COLOR, load_game_option_position_x, load_game_option_position_y);
        }
    }

    remove_screen(home_screen);
    remove_screen(menu_screen);
    remove_screen(savelist_screen);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
