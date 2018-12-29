
#include "SoftRender/SDL2Window.h"
#include <iostream>
using namespace std;

#undef main



int main(int argc, char *argv[])
{

    SDL2Window *win = new SDL2Window(1280, 720);
    win->Run();
    delete win;
    return 0;
}
