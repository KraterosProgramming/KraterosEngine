#pragma once
#include <SDL2/SDL.h>
#include <string>

#include "Rect.h"
#include "Font.h"

namespace KE
{

class Surface
{
    SDL_Surface* sdlSurface;

    void load(SDL_Surface* sdlSurface);
    void unload();

protected:
    friend class Library;
    friend class Renderer;
    friend class Texture;

    Surface();
    ~Surface();

    bool create(int w, int h, const SDL_PixelFormat* format);
    bool create(int w, int h, int depth, char* pixels);
    bool loadFromFile(const std::string &path);
    bool renderText(const Font &font, const std::string &text, const Color &color);

public:
    int getWidth() const;
    int getHeight() const;
    const SDL_PixelFormat *getFormat() const;
    operator SDL_Surface*() const;

    bool blit(Surface &destiny, const Rect &rect) const;
};

}
