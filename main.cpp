/*
** EPITECH PROJECT, 2019
** 3DGameProgram
** File description:
** main
*/


#include "SoftRender/SDL2Window.h"
#include <iostream>
using namespace std;

#undef main



int main(int argc, char *argv[])
{

    SDL2Window win =  SDL2Window(1280, 720);
    win.Run();
    return 0;
}
