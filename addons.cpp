#include "addons.h"

void cap_framerate ( Uint32 starting_tick ){
    if ( ( 1000 / FPS ) > SDL_GetTicks() - starting_tick ){
      SDL_Delay( 1000 / FPS - ( SDL_GetTicks() - starting_tick ) );
    }
};

void initColors(SDL_Surface* gScreen){
    gPink = SDL_MapRGB(gScreen->format, 232, 111, 148);
    gRed = SDL_MapRGB(gScreen->format, 250, 0, 0);
    gBeige = SDL_MapRGB(gScreen->format, 255, 255, 115);
    gBlue = SDL_MapRGB(gScreen->format, 0, 0, 255);
    gDarkblue = SDL_MapRGB(gScreen->format, 111, 114, 120);
    gDarkgreen = SDL_MapRGB(gScreen->format, 100, 120, 100);
}

void printVectorTodos(){
  //Store all to-dos in a vector of pairs (priority, description)
  // 1: current, 2: high, 3: medium, 4: low, 5: future
  std::vector<std::pair<int, std::string>> todos = {

    {1, "REFACTOR loopPlayState() into a separate player class, that has the playing/notplaying/paused etc states, and maybe even the play/pause button rects"},
    {1, "REFACTOR \n button.cpp: add rect dimensions into the class arguments, to avoid having to resize image files"},
    {1, "SDL2 THEORY \n button.cpp: why are the 3rd args of SDL_BlitScaled() and SDL_BlitSurface() different? the SDL_BlitScaled was yoinked from input.cpp scaling logic"},

    {1, "FEATURE \n drawButtonScaled(): the 2nd & 3rd dRectButton args dont scale properly, aspect ratio shenanigans?"},
    {1, "REFACTOR \n input.h: refactor point as a private member with getters"},
    {1, "CLEANUP \n to avoid confusion make sure all variables are declared only either GLOBALLY or LOCALLY"},

    {2, "FEATURE \n handleMenuState(): abstract the render logic into separate state-agnostic functions"},
    {2, "FEATURE \n Make class members private where appropriate"},

    {3, "BACKLOG \n main.cpp: if play rect pressed -> currentState = PLAY_STATE"},
    {3, "BACKLOG \n main.cpp: if gallery rect pressed -> currentState = GAY_STATE"},
    {3, "BACKLOG \n Clicking X to close the game"},
    {3, "BACKLOG \n button.cpp: change playButton sprite on interact using the commented spritesheet drawing logic"},
    {6, "DEPENDS button.cpp: change playButton sprite on interact without a spritesheet"},
    {6, "Rewrite the eventloop as a separate EventListener (mouse events) -> clickable buttons -> main menu -> submenus"},

    {6, "Separate classes from `render.h` to their own header files"},
    {6, "QUESTION: possible to draw mouse using the premade classes Sprite, SpriteGroup or Block"},
    {6, "was adding window_width and window_height return types to initVideo() really necessary when you made it a global/extern function"},

    {4, "Add listeners for ctrl+q and ctrl+w and q to exit the game"},

    {6, "FEATURE \n test if `double delta` timer from main.cpp can be combined with cap_framerate()"},
    {6, "Currently all header files that require SDL libs source them through `render.h` -> `main.h`. \n Delete this superfluous step and directly source the SDL libs through main.h.\n For the affected header files this will require adding includes for the standard libs that are also in render.h (as of now just iostream and vector)."},
    {6, "FEATURE \n implement gl_renderer.cpp (and vk_renderer.cpp) for the SDL_Render stuff and comments"},
    {5, "FEATURE \n physics.h: vect2 to move sprites"},
    {6, "Refactor everything into OOP, with base classes and subclasses"},
    {5, "FEATURE \n button.cpp: implement spritesheet capabilities"},
  };

  std::cout << "### Printing The Autosorted TODO List... ###" << std::endl;

  //print todos by priority
  //for (int priority = 1; priority <= 6; ++priority) {
  for (int priority = 6; priority >= 1; --priority) {
    for (const auto& todo : todos) {
      if (todo.first == priority) {
        std::cout << priority << ". " << todo.second << std::endl;
      }
    }
  }
}
