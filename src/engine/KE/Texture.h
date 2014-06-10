#pragma once
#include <SDL2/SDL.h>
#include <string>

#include "Surface.h"

namespace KE
{

class Texture
{
    SDL_Texture* sdlTexture;
    Point size;

    void load(SDL_Texture* sdlTexture, const Point &size);
    void unload();

public:
    Texture();
    ~Texture();

    const Point getSize() const;
    const Rect getClip() const;
    static std::string getName();

    operator SDL_Texture*() const;

    bool loadFromSurface(const Surface &surface);
    bool loadFromFile(const std::string &path);

    void draw(const Point &position, const Rect &source) const;
};

}
