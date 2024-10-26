#include <SDL.h>
#include <SDL_image.h>
#include <tmx.h>

SDL_Texture* load_tileset_texture(char* filename, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* render_map_to_texture(SDL_Renderer* renderer, tmx_map* map) {
    SDL_Texture* map_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, map->width * map->tile_width, map->height * map->tile_height);
    SDL_SetRenderTarget(renderer, map_texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    tmx_layer* layer = map->ly_head;
    tmx_tileset_list* ts_list = map->ts_head;
    SDL_Texture* tileset_texture = NULL;

    if(ts_list && ts_list->tileset && ts_list->tileset->image) {
        tileset_texture = load_tileset_texture(ts_list->tileset->image->source, renderer);
    }

    while(layer) {
        if(layer->type == L_LAYER) {
            for(int i = 0; i < map->height; i++) {
                for(int j = 0; j < map->width; j++) {
                    unsigned int gid = layer->content.gids[(i * map->width) + j] & TMX_FLIP_BITS_REMOVAL;
                    if(gid != 0 && gid >= ts_list->firstgid) {
                        unsigned int tile_index = gid - ts_list->firstgid;
                        if(tile_index < ts_list->tileset->tilecount) {
                            unsigned int tiles_per_row = ts_list->tileset->image->width / ts_list->tileset->tile_width;
                            unsigned int tile_col = tile_index % tiles_per_row;
                            unsigned int tile_row = tile_index / tiles_per_row;
                            SDL_Rect src_rect = {
                                    .x = tile_col * ts_list->tileset->tile_width,
                                    .y = tile_row * ts_list->tileset->tile_height,
                                    .w = ts_list->tileset->tile_width,
                                    .h = ts_list->tileset->tile_height
                            };
                            SDL_Rect dest_rect = {
                                    .x = j * map->tile_width,
                                    .y = i * map->tile_height,
                                    .w = map->tile_width,
                                    .h = map->tile_height
                            };
                            if(tileset_texture) {
                                SDL_RenderCopy(renderer, tileset_texture, &src_rect, &dest_rect);
                            }
                        }
                    }
                }
            }
        }
        layer = layer->next;
    }

    SDL_SetRenderTarget(renderer, NULL);
    if(tileset_texture) {
        SDL_DestroyTexture(tileset_texture);
    }
    return map_texture;
}
