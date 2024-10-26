#ifndef POCEMON_CHARACTER_H
#define POCEMON_CHARACTER_H

#include "pokemon.h"

typedef struct{
    SDL_Texture* sprite;
    int x;
    int y;
    int width;
    int height;
} Character;

SDL_Texture* load_character_sprite(char* filename, SDL_Renderer* renderer);
Character init_character(SDL_Renderer* renderer, char* sprite_path, int x, int y);
void render_character(SDL_Renderer* renderer, Character* character, int camera_x, int camera_y);

#endif
