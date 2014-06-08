#include "Surface.h"
#include <SDL2/SDL_image.h>
#include "Tools.h"

namespace KE
{

Surface::Surface()
{
    this->sdlSurface = nullptr;
}

Surface::~Surface()
{
    unload();
}


const Point Surface::getSize() const
{
    return Point(sdlSurface->w, sdlSurface->h);
}

const SDL_PixelFormat *Surface::getFormat() const
{
    return sdlSurface->format;
}

Surface::operator SDL_Surface*() const
{
    return sdlSurface;
}

void Surface::load(SDL_Surface* sdlSurface)
{
    unload();
    this->sdlSurface = sdlSurface;
}

void Surface::unload()
{
    if (sdlSurface)
    {
        SDL_FreeSurface(sdlSurface);
        sdlSurface = nullptr;
    }
}

bool Surface::create(const Point &size, const SDL_PixelFormat* format)
{
    SDL_Surface *created = SDL_CreateRGBSurface(0, size.x, size.y, format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask, format->Amask);
    if (!created)
    {
        Error() << "creating surface: " << SDL_GetError();
    }
    else
    {
        load(created);
    }
    return created;
}

bool Surface::create(const Point &size, int depth, char* pixels)
{
    SDL_Surface *created = SDL_CreateRGBSurfaceFrom(pixels, size.x, size.y, depth, size.x * depth, 0, 0, 0, 0);
    if (!created)
    {
        Error() << "creating surface from pixels: " << SDL_GetError();
    }
    else
    {
        load(created);
    }
    return created;
}

void Surface::create(SDL_Surface* sdlSurface)
{
    load(sdlSurface);
}

bool Surface::loadFromFile(const std::string &path)
{
    SDL_Surface* loaded = IMG_Load(path.c_str());
    if (!loaded)
    {
        Error() << "loading file: " << IMG_GetError();
    }
    else
    {
        load(loaded);
    }
    return loaded;
}

bool Surface::blit(Surface &destiny, const Rect &rect) const
{
    if (SDL_BlitSurface(sdlSurface, nullptr, destiny, rect) < 0)
    {
        Error() << "blitting surfaces: " << SDL_GetError();
    }
    else
    {
        return true;
    }
    return false;
}

}
