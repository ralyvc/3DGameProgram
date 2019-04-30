#include "SDL2Window.h"
#include "Camera.h"
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
        _window = SDL_CreateWindow("Solft Render based on SDL2", 30, 30, _width, _height, SDL_WINDOW_POPUP_MENU);
        _surface = SDL_GetWindowSurface(_window);
        _scene = new Scene();
        _renderer = new Renderer(_width, _height, _scene);
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
    unsigned int deltaT = 0;
    unsigned int start = 0;
    unsigned int total = 0;
    while (_isRunning)
    {
        start = SDL_GetTicks();
        ++count;
        UpdateInput();
        _scene->Update(deltaT);
        _renderer->Update(deltaT);
        SwapBuffers();
        deltaT = SDL_GetTicks() - start;
        printf("%2.1d: Frame elapsed time (ms):%d\n",count, deltaT);
        total += deltaT;
    }
}

void SDL2Window::UpdateInput()
{
    if (SDL_PollEvent(&_event))
    {

        switch (_event.type)
        {
        case SDL_QUIT:
            Quit();
            break;
        case SDL_KEYDOWN:
            HandleKey();
            break;
        case SDL_MOUSEWHEEL:
            //_scene->mainCamera

            //_scene->GetCamera()->pos += Vector3f(0, 0, 0);
            _scene->GetCamera()->SetPos(_scene->GetCamera()->GetPos() + _scene->GetCamera()->GetForward() * _event.wheel.y);

            //std::cout << "wheel x:" << _event.wheel.x << " wheel y:" << _event.wheel.y << endl;
            break;
        case SDL_MOUSEBUTTONDOWN:

            isMouseButtonDown = true;
            break;
        case SDL_MOUSEBUTTONUP:
            isMouseButtonDown = false;
            break;
        case SDL_MOUSEMOTION:
        {
            
            if (isMouseButtonDown) 
            {
                thetax -= kPi / 3 * _event.motion.xrel / 1000;
                thetay += kPi / 3 * _event.motion.yrel / 1000;
                auto l = _scene->GetCamera()->GetPos().length();
                Vector3f pos;
                pos.x = cos(thetax) * cos(thetay) * l;
                pos.z = sin(thetax) * cos(thetay) * l;
                pos.y = sin(thetay) * l;
                _scene->GetCamera()->SetPos(pos);
                _scene->GetCamera()->LookAt(Vector3f(0, 0, 0));
                //std::cout << "wheel x:" << _event.motion.xrel << " wheel y:" << _event.motion.xrel << endl;
            }
            
        }
        break;
        default:
        std::cout <<_event.type << endl;
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

void SDL2Window::SwapBuffers()
{
    //Allows surface editing
    SDL_LockSurface(_surface);
    auto pixels = _renderer->GetBuffer();
    //Copy pixels buffer resuls to screen surface
    memcpy(_surface->pixels, pixels->buffer, pixels->mHeight * pixels->mPitch);
    SDL_UnlockSurface(_surface);

    //Apply surface changes to window
    SDL_UpdateWindowSurface(_window);
}

SDL2Window::~SDL2Window()
{
    delete _renderer;
    delete _scene;
    SDL_Quit();
}