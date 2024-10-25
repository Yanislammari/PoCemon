#ifndef SCREEN_H
#define SCREEN_H

typedef struct {
    SDL_Texture** frames;
    int frame_count;
    int current_frame;
    int frame_delay;
    Uint32 last_update_time;
} Screen;

Screen initializeScreen(SDL_Renderer* renderer, const char* imagePath);
void displayScreen(SDL_Renderer* renderer, Screen* screen);
void removeScreen(Screen screen);
void fullScreenWindow(SDL_Window* window);

#endif
