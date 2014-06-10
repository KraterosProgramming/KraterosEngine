#include "Window.h"
#include "Tools.h"

namespace KE
{

Window::Window()
{
    this->sdlWindow = nullptr;
}

void Window::quit()
{
    unload();
    Log() << "window closed";
}

void Window::load(SDL_Window *window)
{
    unload();
    this->sdlWindow = window;
}

void Window::unload()
{
    if (sdlWindow)
    {
        SDL_DestroyWindow(sdlWindow);
        sdlWindow = nullptr;
    }
}

Window::operator SDL_Window*() const
{
    return sdlWindow;
}

bool Window::create(int w, int h, const std::string &title)
{
    SDL_Window *created = SDL_CreateWindow(title.c_str(),
                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           w, h,
                                           SDL_WINDOW_SHOWN);
    if (!created)
    {
        Error() << "creating window: " << SDL_GetError();
    }
    else
    {
        load(created);
    }
    return created;
}

Point Window::getSize() const
{
    Point p;
    SDL_GetWindowSize(sdlWindow, &p.x, &p.y);
    return p;
}

void Window::setSize(const Point &p)
{
    SDL_SetWindowSize(sdlWindow, p.x, p.y);
}

void Window::setTitle(const std::string &title)
{
    SDL_SetWindowTitle(sdlWindow, title.c_str());
}

}
