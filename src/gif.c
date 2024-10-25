#include <stdlib.h>
#include <gif_lib.h>
#include "includes/gif.h"

Gif* load_gif_frames(const char* filename, int* frameCount) {
    GifFileType* gifFile;
    int error;
    Gif* frames = NULL;
    int frame_index = 0;
    gifFile = DGifOpenFileName(filename, &error);

    if(DGifSlurp(gifFile) == GIF_ERROR){
        DGifCloseFile(gifFile, &error);
        return NULL;
    }

    *frameCount = gifFile->ImageCount;
    frames = (Gif*)malloc(*frameCount * sizeof(Gif));

    for(int i = 0; i < *frameCount; i++) {
        SavedImage* image = &gifFile->SavedImages[i];
        Gif* frame = &frames[frame_index];
        frame->width = gifFile->SWidth;
        frame->height = gifFile->SHeight;
        GraphicsControlBlock gcb;

        if(DGifSavedExtensionToGCB(gifFile, i, &gcb) == GIF_OK) {
            frame->delayTime = gcb.DelayTime * 10;
        }
        else {
            frame->delayTime = 0;
        }

        ColorMapObject* colorMap = image->ImageDesc.ColorMap ? image->ImageDesc.ColorMap : gifFile->SColorMap;
        frame->data = (GifByteType*)malloc(frame->width * frame->height * 3 * sizeof(GifByteType));

        for(int j = 0; j < frame->width * frame->height; j++) {
            int colorIndex = image->RasterBits[j];
            GifColorType color = colorMap->Colors[colorIndex];
            frame->data[j * 3] = color.Red;
            frame->data[j * 3 + 1] = color.Green;
            frame->data[j * 3 + 2] = color.Blue;
        }
        frame_index++;
    }

    DGifCloseFile(gifFile, &error);
    return frames;
}
