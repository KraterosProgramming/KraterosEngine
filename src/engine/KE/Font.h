#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "Color.h"
#include "Texture.h"
#include "Tools.h"

namespace KE
{

class Font
{
    enum Style
    {
        Normal = 0x0,
        Bold = 0x1,
        Italic = 0x2,
        Underline = 0x4,
        StrikeThrough = 0x8,
    };

    TTF_Font *ttfFont;

    void load(TTF_Font *ttfFont);
    void unload();

public:
    Font();
    ~Font();

    operator TTF_Font*() const;

    bool loadFromFile(const std::string &path);
    bool loadFromFile(const std::string &path, int size, int style = 0);

    bool renderOnSurface(Surface &out, const std::string &text, const Color &color) const;
    bool renderOnTexture(Texture &out, const std::string &text, const Color &color) const;
};

}
