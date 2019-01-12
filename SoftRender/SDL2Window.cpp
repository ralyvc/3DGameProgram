#include "SDL2Window.h"
#include <iostream>

 SDL2Window::SDL2Window(int width, int height)
{
    try
    {
        if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            throw SDL_GetError();
        }
        _width = width;
        _height = height;
        _window = SDL_CreateWindow("Solft Render based on SDL2", 30, 30, _width, _height,  SDL_WINDOW_POPUP_MENU);
        _surface = SDL_GetWindowSurface(_window);

        _renderer = new Renderer( _width, _height);
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
    int count = 0;
    while (_isRunning)
    {
        ++count;
        Uint32 start = SDL_GetTicks();
        UpdateInput();
        Clear();
        Draw();
        SwapBuffers();
        //Uint32 deltaT = SDL_GetTicks() - start;
        //printf("%2.1d: Frame elapsed time (ms):%d\n",count, deltaT);
    }

}

void SDL2Window::Clear()
{
    _renderer->clear();
}


void SDL2Window::Draw()
{
    _renderer->drawFlatBottomTriangle(Vector3i(300, 300, 0), Vector3i(100, 500, 0), Vector3i(500, 500, 0),0xff000034);

    _renderer->drawFlatBottomTriangle(Vector3i(400, 400, 0), Vector3i(100, 500, 0), Vector3i(500, 500, 0),0x00ff0056);
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



void SDL2Window::SwapBuffers(){
    //Allows surface editing 
    SDL_LockSurface(_surface);
    auto pixels = _renderer->GetBuffer();
    //Copy pixels buffer resuls to screen surface
    memcpy(_surface->pixels,pixels->buffer, pixels->mHeight*pixels->mPitch);
    SDL_UnlockSurface(_surface);

    //Apply surface changes to window
    SDL_UpdateWindowSurface(_window);

}

SDL2Window::~SDL2Window()
{
    delete _renderer;
    SDL_Quit();
}