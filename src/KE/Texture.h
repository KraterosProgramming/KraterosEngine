#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Surface.h"

namespace KE
{

template<class> class Collection;

class Texture
{
    SDL_Texture* sdlTexture;
    int w, h;

    void load(SDL_Texture* sdlTexture, int w, int h);
    void unload();

protected:
    friend class Collection<Texture>;
    Texture();
    ~Texture();

    bool loadFromSurface(const Surface &surface);
    bool loadFromSurfaceVec(const std::vector<Surface> &surfaces);
    bool loadFromFile(const std::string &path);
    bool renderText(const Font &font, const std::string &text, const Color &color);

public:
    operator SDL_Texture*() const;

    int getWidth();
    int getHeight();
    static std::string getName();

    void draw(const Point &position, const Rect &source) const;
};

}
