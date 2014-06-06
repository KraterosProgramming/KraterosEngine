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

int Surface::getWidth() const
{
    return sdlSurface->w;
}

int Surface::getHeight() const
{
    return sdlSurface->h;
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

bool Surface::create(int w, int h, const SDL_PixelFormat* format)
{
    SDL_Surface *created = SDL_CreateRGBSurface(0, w, h, format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask, format->Amask);
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

bool Surface::create(int w, int h, int depth, char* pixels)
{
    SDL_Surface *created = SDL_CreateRGBSurfaceFrom(pixels, w, h, depth, w * depth, 0, 0, 0, 0);
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

bool Surface::renderText(const Font &font, const std::string &text, const Color &color)
{
    SDL_Surface *rendered = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!rendered)
    {
        Error() << "rendering text: " << TTF_GetError();
    }
    else
    {
        load(rendered);
    }
    return rendered;
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
