#include "../Third/include/SDL2/SDL.h"
class SDL2Window
{
  private:
    bool _isRunning;
    SDL_Window *_window;
    int _width;
    int _height;
    SDL_Surface *_surface;
    SDL_Event _event;

  public:
    SDL2Window(int width, int height);
    void Run();
    ~SDL2Window();

  private:
    void UpdateInput();
    void Update();
    void Show();
    void Quit();
    void HandleKey();
};
