#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace KE
{

class Window
{
    SDL_Window *sdlWindow;

    void load(SDL_Window *window);
    void unload();

protected:
    friend class App;

    Window();
    ~Window();

    bool create(int w, int h, const std::string &title);

public:
    operator SDL_Window*() const;
};

}
