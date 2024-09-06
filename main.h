#ifndef MAIN_H
#define MAIN_H // MAIN.H "GLOBALS.H"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 320
#define FPS 15

void initVideo(int window_width, int window_height);
void initMixer();

struct WindowDimensions{
    int wSize;
    int hSize;
    int xPosi;
    int yPosi;
};

// Declaring certain variables as extern.
extern SDL_Window *gWindow;
extern SDL_Surface *gScreen;

extern Uint32 gPink;
extern Uint32 gRed;
extern Uint32 gBeige;
extern Uint32 gBlue;
extern Uint32 gDarkblue;
extern Uint32 gDarkgreen;

#endif // MAIN_H
