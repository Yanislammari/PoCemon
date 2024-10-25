#ifndef GIF_H
#define GIF_H

#include <gif_lib.h>

typedef struct {
    int width;
    int height;
    int delayTime;
    GifByteType* data;
} Gif;

Gif* load_gif_frames(char* filename, int* frameCount);

#endif
