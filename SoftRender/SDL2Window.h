#include "../Third/include/SDL2/SDL.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Color.h"
#include "../Math/Matrix.hpp"
#pragma once

class SDL2Window
{
  private:
    bool _isRunning;
    SDL_Window *_window;
    int _width;
    int _height;
    SDL_Surface *_surface;
    SDL_Event _event;
    Renderer *_renderer;


  public:
    SDL2Window(int width, int height);
    void Run();
    void Draw();
    void Clear();
    ~SDL2Window();

  private:
    void UpdateInput();
    void Update();
    void Quit();
    void HandleKey();
    void SwapBuffers();
};
