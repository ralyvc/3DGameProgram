#include "SDL2Window.h"
#include <iostream>

 SDL2Window::SDL2Window(int width, int height)
{
    try
    {
        if (SDL_Init(SDL_INIT_VIDEO == -1))
        {
            throw SDL_GetError();
        }
        _width = width;
        _height = height;
        _window = SDL_CreateWindow("Solft Render based on SDL2", 30, 30, _width, _height,  SDL_WINDOW_POPUP_MENU);
        _surface = SDL_GetWindowSurface(_window);

        _canvas = new Canvas((uint32_t*)_surface->pixels, _width, _height);
        _isRunning = true;
    }
    catch (const char *s)
    {
        std::cerr << s << std::endl;
        return;
    }
}

void SDL2Window::Run()
{

    while (_isRunning)
    {
        SDL_LockSurface(_surface);
        Clear();
        UpdateInput();
        Draw();
        Show();
        SDL_UnlockSurface(_surface);
    }
}

void SDL2Window::Clear()
{
    _canvas->clear();
}


void SDL2Window::Draw()
{
    _canvas->BresenhamLine(-34,345,456,720,-1234);
}
void SDL2Window::UpdateInput()
{
    if (SDL_PollEvent(&_event)) {
        
        switch (_event.type)
        {
        case SDL_QUIT:
            Quit();
            break;
        case SDL_KEYDOWN:
            HandleKey();
            break;
        default:
            break;
        }
    }
    
}

void SDL2Window::HandleKey()
{
    SDL_Keycode keyCode = _event.key.keysym.sym;
    
    switch (keyCode)
    {
        case SDLK_ESCAPE:
            Quit();
            break;
    
        default:
            break;
    }
}

void SDL2Window::Quit()
{
    _isRunning = false;
}

void SDL2Window::Show()
{
    SDL_UpdateWindowSurface(_window);
}

SDL2Window::~SDL2Window()
{
    delete _canvas;
}