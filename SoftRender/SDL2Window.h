#include "../Third/include/SDL2/SDL.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Color.h"
#include "Matrix.h"
#include "Scene.h"
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
    Scene *_scene;

    bool isMouseButtonDown = false;
    float thetax = 0;
    float thetay = 0;


  public:
    SDL2Window(int width, int height);
    void Run();

    ~SDL2Window();

  private:
    void UpdateInput();
    void Update();
    void Quit();
    void HandleKey();
    void SwapBuffers();
};
