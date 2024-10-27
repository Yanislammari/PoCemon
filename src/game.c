#include <SDL.h>
#include <SDL_ttf.h>
#include <tmx.h>
#include "includes/screen.h"
#include "includes/game.h"
#include "includes/text.h"
#include "includes/map.h"
#include "includes/character.h"

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
    tmx_map* map = NULL;
    SDL_Texture* map_texture = NULL;
    Character player;

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
                            map = tmx_load("../assets/map/map_main/map.tmx");
                            map_texture = render_map_to_texture(renderer, map);
                            game_state = STATE_GAME;
                        }
                    }
                    else if(e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP) {
                        menu_selected_option = 1 - menu_selected_option;
                    }
                }
                else if(game_state == STATE_GAME) {
                    int speed = 10;
                    if(e.key.keysym.sym == SDLK_LEFT) {
                        player.x -= speed;
                    }
                    else if(e.key.keysym.sym == SDLK_RIGHT) {
                        player.x += speed;
                    }
                    else if(e.key.keysym.sym == SDLK_UP) {
                        player.y -= speed;
                    }
                    else if(e.key.keysym.sym == SDLK_DOWN) {
                        player.y += speed;
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
        else if(game_state == STATE_GAME && map_texture) {
            int camera_x = player.x + player.width / 2 - WINDOW_WIDTH / 2;
            int camera_y = player.y + player.height / 2 - WINDOW_HEIGHT / 2;
            if(camera_x < 0) {
                camera_x = 0;
            }
            if(camera_y < 0) {
                camera_y = 0;
            }
            if(camera_x > map->width * map->tile_width - WINDOW_WIDTH) {
                camera_x = map->width * map->tile_width - WINDOW_WIDTH;
            }
            if(camera_y > map->height * map->tile_height - WINDOW_HEIGHT) {
                camera_y = map->height * map->tile_height - WINDOW_HEIGHT;
            }
            SDL_Rect camera_rect = {camera_x, camera_y, WINDOW_WIDTH, WINDOW_HEIGHT };
            SDL_RenderCopy(renderer, map_texture, &camera_rect, NULL);
            render_character(renderer, &player, camera_x, camera_y);
            SDL_Rect player_rect = {player.x - camera_x, player.y - camera_y, player.width, player.height };
            SDL_RenderCopy(renderer, player.sprite, NULL, &player_rect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if(map_texture) {
        SDL_DestroyTexture(map_texture);
    }

    remove_screen(home_screen);
    remove_screen(menu_screen);
    remove_screen(savelist_screen);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}