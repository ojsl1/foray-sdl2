#include "main.h" // globals
#include "render.h"

SDL_Window *gWindow = nullptr;
SDL_Surface *gScreen = nullptr;

void RendererBase::cap_framerate ( Uint32 starting_tick ){
    if ( ( 1000 / FPS ) > SDL_GetTicks() - starting_tick ){
      SDL_Delay( 1000 / FPS - ( SDL_GetTicks() - starting_tick ) );
    }
};

void RendererBase::initColors(SDL_Surface *gScreen){
    gPink = SDL_MapRGB(gScreen->format, 232, 111, 148);
    gRed = SDL_MapRGB(gScreen->format, 250, 0, 0);
    gBeige = SDL_MapRGB(gScreen->format, 255, 255, 115);
    gBlue = SDL_MapRGB(gScreen->format, 0, 0, 255);
    gDarkblue = SDL_MapRGB(gScreen->format, 111, 114, 120);
    gDarkgreen = SDL_MapRGB(gScreen->format, 100, 120, 100);
}

void RendererBase::initVideo( int window_width, int window_height ){
    SDL_Init( SDL_INIT_EVERYTHING );
    IMG_Init( IMG_INIT_PNG );
    
    // Create the window
    gWindow = SDL_CreateWindow( "Metadata fetcher",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                window_width, // window_width
                                window_height, // window_height
                                SDL_WINDOW_RESIZABLE
                                //SDL_WINDOW_FULLSCREEN_DESKTOP
                                );

    if ( gWindow == NULL ){
      std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
      SDL_Quit();
      return;
    }

    //Note: this disables SDL_WINDOW_FULLSCREEN_DESKTOP
    SDL_SetWindowBordered(gWindow, SDL_TRUE);
    
    gScreen = SDL_GetWindowSurface(gWindow);
    if ( gScreen == NULL ){
      std::cerr << "SDL_ GetWindowSurface Error: " << SDL_GetError() << std::endl;
      SDL_DestroyWindow(gWindow);
      SDL_Quit();
      return;
    }
}

void RendererBase::Clear(){
  // Clear the screen (optional, depends on app logic)
  /*
  if (!gScreen){
    std::cout << "gScreen invalid during ren.Clear, unable to clear." << std::endl;
  }
  */

  SDL_FillRect(gScreen, NULL, SDL_MapRGB(gScreen->format, 255, 50, 255));
}

void RendererBase::Draw(Mouse &mouse, Button &buttonExit, Button &buttonTests,
     Button &buttonDrop, Button &buttonMute, Button &buttonPause,
     Button &buttonFrame, Button &buttonInfoFrame, Button &buttonBackground
     ){
  Clear();
  buttonBackground.Draw(gScreen);
  buttonFrame.Draw(gScreen);
  buttonInfoFrame.Draw(gScreen);
  buttonDrop.DrawScaled(gScreen);
  buttonMute.Draw(gScreen);
  buttonPause.Draw(gScreen);
  buttonExit.Draw(gScreen);

  #if ALLEYS
  buttonTests.Draw(gScreen);
  if (buttonTests.hasintersection){
    DrawTests();
  };
  #endif // ALLEYS

  mouse.Draw(gScreen); // draw mouse last so it's always on top
}

void RendererBase::Present(){
  // Present the frame/update the new frame, same as SDL_RenderPresent()
  SDL_UpdateWindowSurface(gWindow);
 
  /*
  const char* error = SDL_GetError();
  if (*error != '\0') {
    std::cerr << "SDL Error during present: " << error << std::endl;
    SDL_ClearError();
  }
  */
}

void RendererBase::Shutdown(SDL_Window *gWindow, WindowDimensions dims){
    //SDL_SetWindowSize( gWindow, dims.wSize, dims.hSize ); //enforce size
    //SDL_SetWindowPosition( gWindow, dims.xPosi, dims.yPosi ); //enforce position
    SDL_GetWindowPosition( gWindow, &dims.xPosi, &dims.yPosi );
    std::cout << "Exit Position: " << dims.xPosi << "," << dims.yPosi << std::endl;
    std::cout << "Exit Size: " << dims.wSize << "," << dims.hSize << " [TODO: Doesnt update after resizing]" << std::endl;
    std::cout << "FPS: " << FPS << std::endl;

    if (gScreen != NULL) {
      SDL_FreeSurface(gScreen);
      gScreen = NULL;
    }
   
    /*
    if (gFont != NULL) {
      TTF_CloseFont(gFont);
      gFont = NULL;
    }
    TTF_Quit();
    */

    if (gWindow != NULL) {
      SDL_DestroyWindow(gWindow);
      gWindow = NULL;
    }

    IMG_Quit();
    SDL_Quit();

    std::cout << "Exit succesfully" << std::endl;
}

#if ALLEYS
void RendererBase::DrawTests(){
  // ALLEY. Create Sprites
  Sprite object( gRed, WINDOW_WIDTH/2, WINDOW_HEIGHT/2 );
  Sprite another( gBlue, WINDOW_WIDTH/2-100, WINDOW_HEIGHT/2+20 );

  // ALLEY. Create Block sprites
  Block block1( gPink, 120, 30 );
  Block block2( gPink, 100, 15 );
  block1.set_image( "assets/cosmox2.png" );
  block2.set_image( "assets/avatar.bmp" );

  /*
  TODO: ALLEY. Trying to blit cursor along with other sprites
  Block block3mouse( blue, 130, 40 );
  block3mouse.set_image( "assets/mouse.png" );
  SpriteGroup pointers;
  pointers.add( &block3mouse );
  pointers.draw( gScreen ); // draw to mouse not to screen
  */

  // ALLEY. Create a SpriteGroup & add previously created Blocks to it
  SpriteGroup active_sprites;
  active_sprites.add( &block2 );
  active_sprites.add( &block1 );
  active_sprites.add( &another );
  active_sprites.add( &object );
  object.draw( gScreen );

  // ALLEY. Test if SpriteGroup contains a specified sprite_object
  //std::cout << active_sprites.has( another ) << std::endl; // TODO: Print only once instead of spamming

  // ALLEY. Blit the whole SpriteGroup
  active_sprites.draw(gScreen);
}
#endif // ALLEYS
