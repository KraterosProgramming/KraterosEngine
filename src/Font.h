#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "Color.h"

namespace KE
{

template<class> class Collection;

class Font
{
    TTF_Font *sdlFont;

    void load(TTF_Font *sdlFont);
    void unload();

protected:
    friend class Collection<Font>;
    friend class Surface;

    Font();
    ~Font();

    bool loadFromFile(const std::string &path, int size, int style = 0);
    bool loadFromFile(const std::string &path);

    SDL_Surface* renderText(const std::string &text, const Color &color);
    bool renderLines(const std::string &text, const Color &color, std::vector<SDL_Surface*> vec);

public:
    static std::string getName();
    operator TTF_Font*() const;
};

}
