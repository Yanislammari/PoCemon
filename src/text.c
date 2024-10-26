#include <SDL_ttf.h>
#include "includes/text.h"

void render_text(SDL_Renderer* renderer, TTF_Font* font, char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest_rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
