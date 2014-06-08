#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "Color.h"
#include "Texture.h"

namespace KE
{

template<class> class Collection;

class Font
{
    TTF_Font *sdlFont;

    void load(TTF_Font *sdlFont);
    void unload();

public:
    Font();
    ~Font();

    operator TTF_Font*() const;

    bool loadFromFile(const std::string &path, int size, int style = 0);
    bool loadFromFile(const std::string &path);
    bool renderOnSurface(Surface &out, const std::string &text, const Color &color) const;
    bool renderOnTexture(Texture &out, const std::string &text, const Color &color) const;
};

}
