#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <tmx.h>
#include <stdlib.h>
#include <time.h>
#include "includes/screen.h"
#include "includes/text.h"
#include "includes/map.h"
#include "includes/character.h"
#include "includes/game.h"
#include "includes/pokemon.h"

void draw_health_bar(SDL_Renderer* renderer, int x, int y, int width, int height, float percent) {
    SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
    SDL_Rect background_bar = {x, y, width, height };
    SDL_RenderFillRect(renderer, &background_bar);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect health_bar = {x, y, (int) (width * percent), height};
    SDL_RenderFillRect(renderer, &health_bar);
}

void run_game() {
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* window = SDL_CreateWindow("PoCemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("../assets/font/Daydream.ttf", 24);

    Mix_Music* home_screen_background_music;
    Mix_Music* menu_screen_background_music;
    Mix_Music* game_screen_background_music;
    Mix_Music* battle_screen_background_music;

    home_screen_background_music = Mix_LoadMUS("../assets/sound/music/home_screen_music.mp3");
    Mix_PlayMusic(home_screen_background_music, -1);

    Screen home_screen = initialize_screen(renderer, "../assets/screen/home_screen.gif");
    enum GameState game_state = STATE_HOME;

    int pokemon_count = 0;
    Pokemon* pokemons = get_pokemons(&pokemon_count);

    int quit = 0;
    SDL_Event e;
    Screen menu_screen;
    Screen savelist_screen;
    int menu_selected_option = 0;
    int battle_selected_option = 0;
    SDL_Color WHITE_COLOR = {255, 255, 255};
    SDL_Color BLACK_COLOR = {0, 0, 0};
    SDL_Color BLUE_COLOR = {0, 0, 255};
    tmx_map* map = NULL;
    SDL_Texture* map_texture = NULL;
    Character player;
    Pokemon wild_pokemon;
    SDL_Texture* wild_pokemon_texture = NULL;

    srand(time(NULL));

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
                        Mix_FreeMusic(home_screen_background_music);
                        menu_screen_background_music = Mix_LoadMUS("../assets/sound/music/menu_screen_music.mp3");
                        Mix_PlayMusic(menu_screen_background_music, -1);
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
                            Mix_FreeMusic(menu_screen_background_music);
                            game_screen_background_music = Mix_LoadMUS("../assets/sound/music/game_screen_music.mp3");
                            Mix_PlayMusic(game_screen_background_music, -1);
                            map = tmx_load("../assets/map/map_main/map.tmx");
                            map_texture = render_map_to_texture(renderer, map);
                            player = init_character(renderer, "../assets/sprite/sprite.png", 300, 300);
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
                    if(rand() % 100 == 0) {
                        int random_index = rand() % pokemon_count;
                        wild_pokemon = pokemons[random_index];
                        wild_pokemon.current_pv = wild_pokemon.total_pv;
                        wild_pokemon_texture = load_character_sprite(wild_pokemon.sprite, renderer);
                        Mix_FreeMusic(game_screen_background_music);
                        battle_screen_background_music = Mix_LoadMUS("../assets/sound/music/battle_screen_music.mp3");
                        Mix_PlayMusic(battle_screen_background_music, -1);
                        game_state = STATE_BATTLE;
                    }
                }
                else if(game_state == STATE_BATTLE) {
                    if(e.key.keysym.sym == SDLK_DOWN) {
                        battle_selected_option = (battle_selected_option + 1) % 4;
                    }
                    else if(e.key.keysym.sym == SDLK_UP) {
                        battle_selected_option = (battle_selected_option - 1 + 4) % 4;
                    }
                    else if(e.key.keysym.sym == SDLK_RETURN) {
                        switch(battle_selected_option) {
                            case 0:
                                wild_pokemon.current_pv -= player.squad[0].atk - wild_pokemon.def;  // Réduit les PV actuels du Pokémon sauvage
                                player.squad[0].current_pv -= wild_pokemon.atk - player.squad[0].def;
                                if(wild_pokemon.current_pv < 0){
                                    wild_pokemon.current_pv = 0;
                                    Mix_FreeMusic(battle_screen_background_music);
                                    game_screen_background_music = Mix_LoadMUS("../assets/sound/music/game_screen_music.mp3");
                                    Mix_PlayMusic(game_screen_background_music, -1);
                                    game_state = STATE_GAME;
                                    break;
                                }
                                break;
                            case 1:  // TODO: BAG LOGIC
                                break;
                            case 2:  // TODO: SWITCH POKEMON LOGIC
                                break;
                            case 3:
                                Mix_FreeMusic(battle_screen_background_music);
                                game_screen_background_music = Mix_LoadMUS("../assets/sound/music/game_screen_music.mp3");
                                Mix_PlayMusic(game_screen_background_music, -1);
                                game_state = STATE_GAME;
                                break;
                            default:
                                break;
                        }
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
        else if(game_state == STATE_BATTLE) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Blanc
            SDL_RenderClear(renderer);

            SDL_Rect player_pokemon_rect = {50, 400, 200, 200};  // Position et taille du sprite
            SDL_Texture* first_pokemon_squad_sprite = load_character_sprite(player.squad[0].sprite, renderer);
            SDL_RenderCopy(renderer, first_pokemon_squad_sprite, NULL, &player_pokemon_rect);

            SDL_Rect wild_pokemon_rect = {550, 50, 200, 200};  // Position et taille du sprite
            SDL_RenderCopy(renderer, wild_pokemon_texture, NULL, &wild_pokemon_rect);

            draw_health_bar(renderer, 50, 370, 200, 20, (float) player.squad[0].current_pv / player.squad[0].total_pv);
            render_text(renderer, font, player.squad[0].nom, BLACK_COLOR, 50, 560);

            draw_health_bar(renderer, 550, 20, 200, 20, (float) wild_pokemon.current_pv / wild_pokemon.total_pv);
            render_text(renderer, font, wild_pokemon.nom, BLACK_COLOR, 550, 210);

            render_text(renderer, font, "Attaquer", battle_selected_option == 0 ? BLUE_COLOR : BLACK_COLOR, 400, 450);
            render_text(renderer, font, "Sac", battle_selected_option == 1 ? BLUE_COLOR : BLACK_COLOR, 400, 480);
            render_text(renderer, font, "Changer Pokemon", battle_selected_option == 2 ? BLUE_COLOR : BLACK_COLOR, 400, 510);
            render_text(renderer, font, "Fuir", battle_selected_option == 3 ? BLUE_COLOR : BLACK_COLOR, 400, 540);
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

    free_pokemons(pokemons, pokemon_count);
}
