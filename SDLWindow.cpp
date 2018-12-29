
#include <iostream>
#include "SDL2/SDL.h"
using namespace std;


#undef main

void pressESCtoQuit();
void doSomeLoopThings();

int main(int argc,char* argv[])
{
    try {
        if ( SDL_Init(SDL_INIT_VIDEO == -1 ))
            throw SDL_GetError();
    }
    catch ( const char* s ) {
        std::cerr << s << std::endl;
        return -1;
    }
    atexit(SDL_Quit);

    //SDL_RenderSetViewport(640, 480, 32, SDL_SWSURFACE);
    SDL_Window *window = SDL_CreateWindow("hhh", 0, 0, 1024, 768,  SDL_WINDOW_SHOWN);
   // SDL_Renderer *ren = SDL_GetRenderer(window);
   // SDL_Rect rect;
    //SDL_RenderSetViewport(ren,&rect);
    std::cout << "Program is running, press ESC to quit./n";
    pressESCtoQuit();
    std::cout << "GAME OVER" << std::endl;

    return 0;
}

void pressESCtoQuit()
{
    std::cout << "pressESCtoQuit() function begin/n";
    bool gameOver = false;
    while( gameOver == false ){
        SDL_Event gameEvent;
        SDL_PollEvent(&gameEvent);
        if ( &gameEvent != 0 ){
            if ( gameEvent.type == SDL_QUIT ){
                gameOver = true;
            }
            if ( gameEvent.type == SDL_KEYDOWN ){
                if ( gameEvent.key.keysym.sym == SDLK_ESCAPE ){
                    gameOver = true;
                }
            }
        }
        doSomeLoopThings();
    }
    return;
}

void doSomeLoopThings()
{
    std::cout << ".";
    return;
}
