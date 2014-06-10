#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "Rect.h"

namespace KE
{

class Surface
{
    SDL_Surface* sdlSurface;

    void load(SDL_Surface* sdlSurface);
    void unload();

public:
    Surface();
    ~Surface();

    const Point getSize() const;
    const SDL_PixelFormat *getFormat() const;

    operator SDL_Surface*() const;

    bool create(const Point &size, const SDL_PixelFormat* format);
    bool create(const Point &size, int depth, char* pixels);
    void create(SDL_Surface* sdlSurface);
    bool loadFromFile(const std::string &path);

    bool blit(Surface &destiny, const Rect &rect) const;
};

}
