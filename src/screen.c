#include <SDL.h>
#include "includes/gif.h"
#include "includes/screen.h"

Screen initializeScreen(SDL_Renderer* renderer, const char* imagePath) {
    Screen screen;
    int frame_count;
    Gif* gif_frames = load_gif_frames(imagePath, &frame_count);
    screen.frames = (SDL_Texture**)malloc(frame_count * sizeof(SDL_Texture*));
    screen.frame_count = frame_count;
    screen.current_frame = 0;
    screen.frame_delay = gif_frames[0].delayTime;
    screen.last_update_time = SDL_GetTicks();

    for(int i = 0; i < frame_count; i++) {
        SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
                gif_frames[i].data,
                gif_frames[i].width,
                gif_frames[i].height,
                24,
                gif_frames[i].width * 3,
                0x0000FF,
                0x00FF00,
                0xFF0000,
                0
        );

        screen.frames[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        free(gif_frames[i].data);
    }
    free(gif_frames);
    return screen;
}

void displayScreen(SDL_Renderer* renderer, Screen* screen) {
    Uint32 current_time = SDL_GetTicks();
    if(current_time - screen->last_update_time >= screen->frame_delay) {
        screen->current_frame = (screen->current_frame + 1) % screen->frame_count;
        screen->last_update_time = current_time;
    }
    SDL_RenderClear(renderer);
    SDL_Texture* current_texture = screen->frames[screen->current_frame];
    if(current_texture) {
        SDL_RenderCopy(renderer, current_texture, NULL, NULL);
    }
}

void removeScreen(Screen screen) {
    for(int i = 0; i < screen.frame_count; i++) {
        SDL_DestroyTexture(screen.frames[i]);
    }
    free(screen.frames);
}

void fullScreenWindow(SDL_Window* window) {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}
