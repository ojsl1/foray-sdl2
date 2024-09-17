#include "button.h"
#include "input.h" // Button::detectCursor depends on the Mouse class

Button::Button(int x, int y, int width, int height, const char* buttonImagePath)
  : sRectButton{0, 0, width, height},    // Initialization list
    rawButton(NULL),
    scaledButton(NULL),
    selected(false)
    // TODO Without this init list the buttons gets drawn at topleft, why?
{
    dRectButton = {x, y, width, height}; //x,y,w,h

    if (!buttonImagePath){
      buttonImagePath = "resources/texture-error.png";
    }

    rawButton = IMG_Load(buttonImagePath);
    if (!rawButton){
      SDL_Log("Failed to load image: %s, SDL_Image Error: %s", buttonImagePath, IMG_GetError());
      rawButton = IMG_Load("resources/texture-error.png");
      if (!rawButton){
        SDL_Log("Failed to load fallback image: resources/texture-error.png, SDL_Image Error: %s", IMG_GetError());
        return;
      }
    }
}

Button::~Button(){
  if (rawButton){
    SDL_FreeSurface(rawButton);
  }
}

void Button::detectCursor( Mouse &mouse){
      if ( SDL_HasIntersection(&dRectButton, &mouse.point) ){
          selected = true;
          std::cout << "hasintersection" << std::endl;
      }else{
          selected = false;
      }
}

void Button::drawButton(SDL_Surface *gScreen){
    SDL_BlitSurface(rawButton, NULL, gScreen, &dRectButton);
}

void Button::drawButtonScaled(SDL_Surface *gScreen){
    // The size of the rectangle the button will be drawn on ie. doesnt resize the image itself
    scaledButton = SDL_CreateRGBSurface(0, dRectButton.w, dRectButton.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (!scaledButton){
      SDL_Log("Failed to create scaled button surface, SDL Error: %s", SDL_GetError());
      return;
    }

    // First scale the rawButton on the scaledButton surface
    SDL_BlitScaled(rawButton, NULL, scaledButton, &dRectButton);
    // Blit the scaledButton onto the screen
    SDL_BlitSurface(scaledButton, NULL, gScreen, &dRectButton);
}
