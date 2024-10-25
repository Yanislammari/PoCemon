#ifndef SCREEN_H
#define SCREEN_H

typedef struct {
    SDL_Texture** frames;
    int frame_count;
    int current_frame;
    int frame_delay;
    Uint32 last_update_time;
} Screen;

Screen initialize_screen(SDL_Renderer* renderer, char* imagePath);
void display_screen(SDL_Renderer* renderer, Screen* screen);
void remove_screen(Screen screen);
void full_screen_window(SDL_Window* window);

#endif
