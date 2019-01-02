#include "../Third/include/SDL2/SDL.h"
#include "Canvas.h"
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
    Canvas *_canvas;

  public:
    SDL2Window(int width, int height);
    void Run();
    void Draw();
    void Clear();
    ~SDL2Window();

  private:
    void UpdateInput();
    void Update();
    void Show();
    void Quit();
    void HandleKey();
};
