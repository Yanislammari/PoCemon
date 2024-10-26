#include <stdlib.h>
#include <gif_lib.h>
#include "includes/gif.h"

Gif* load_gif_frames(char* filename, int* frame_count) {
    GifFileType* gif_file;
    int error;
    Gif* frames = NULL;
    int frame_index = 0;
    gif_file = DGifOpenFileName(filename, &error);
    DGifSlurp(gif_file);
    *frame_count = gif_file->ImageCount;
    frames = (Gif*) malloc(*frame_count * sizeof(Gif));

    for(int i = 0; i < *frame_count; i++) {
        SavedImage* image = &gif_file->SavedImages[i];
        Gif* frame = &frames[frame_index];
        frame->width = gif_file->SWidth;
        frame->height = gif_file->SHeight;
        GraphicsControlBlock gcb;

        if(DGifSavedExtensionToGCB(gif_file, i, &gcb) == GIF_OK) {
            frame->delay_time = gcb.DelayTime * 10;
        }
        else {
            frame->delay_time = 0;
        }

        ColorMapObject* color_map = image->ImageDesc.ColorMap ? image->ImageDesc.ColorMap : gif_file->SColorMap;
        frame->data = (GifByteType*) malloc(frame->width * frame->height * 3 * sizeof(GifByteType));

        for(int j = 0; j < frame->width * frame->height; j++) {
            int color_index = image->RasterBits[j];
            GifColorType color = color_map->Colors[color_index];
            frame->data[j * 3] = color.Red;
            frame->data[j * 3 + 1] = color.Green;
            frame->data[j * 3 + 2] = color.Blue;
        }
        frame_index++;
    }

    DGifCloseFile(gif_file, &error);
    return frames;
}
