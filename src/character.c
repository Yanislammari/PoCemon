#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "includes/character.h"
#include "includes/pokemon.h"

SDL_Texture* load_character_sprite(char* filename, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filename);
    if(!surface) {
        fprintf(stderr, "Unable to load image %s: %s\n", filename, IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(!texture) {
        fprintf(stderr, "Unable to create texture from %s: %s\n", filename, SDL_GetError());
    }

    return texture;
}

Character init_character(SDL_Renderer* renderer, char* sprite_path, int x, int y) {
    Character character;
    character.sprite = load_character_sprite(sprite_path, renderer);
    character.x = x;
    character.y = y;
    int original_width;
    int original_height;
    SDL_QueryTexture(character.sprite, NULL, NULL, &original_width, &original_height);
    character.width = original_width * 2;
    character.height = original_height * 2;
    character.squad = malloc(sizeof(Pokemon) * 6);
    int pokemon_count;
    character.squad[0] = get_pokemons(&pokemon_count)[0];
    return character;
}

void render_character(SDL_Renderer* renderer, Character* character, int camera_x, int camera_y) {
    SDL_Rect dest_rect = {character->x - camera_x, character->y - camera_y, character->width, character->height };
    SDL_RenderCopy(renderer, character->sprite, NULL, &dest_rect);
}
