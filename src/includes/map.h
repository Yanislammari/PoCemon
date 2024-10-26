#ifndef POCEMON_MAP_H
#define POCEMON_MAP_H

SDL_Texture* load_tileset_texture(char* filename, SDL_Renderer* renderer);
SDL_Texture* render_map_to_texture(SDL_Renderer* renderer, tmx_map* map);

#endif
