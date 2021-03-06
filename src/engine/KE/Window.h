#pragma once
#include <SDL2/SDL.h>
#include <string>

#include "Point.h"

namespace KE
{

class Window
{
    SDL_Window *sdlWindow;

    void load(SDL_Window *window);
    void unload();

protected:
    friend class Game;
    friend class Renderer;

    Window();

    void quit();

    bool create(int w, int h, const std::string &title);

    Point getSize() const;
    void setSize(const Point &p);
    void setTitle(const std::string &title);

public:
    operator SDL_Window*() const;
};

}
