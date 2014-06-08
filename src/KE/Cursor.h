#pragma once
#include <SDL2/SDL.h>

#include "Surface.h"
#include "Point.h"

namespace KE
{

class Cursor
{
    SDL_Cursor* sdlCursor;

    void load(SDL_Cursor* sdlCursor);
    void unload();

public:
    static std::string getName();

    using Type = SDL_SystemCursor;

    Cursor();
    ~Cursor();

    // TODO: create cursor?
    //bool create(int w, int h, const SDL_PixelFormat* format);
    //bool create(int w, int h, int depth, char* pixels);
    bool createFromSurface(const Surface &surface, const Point &p);
    bool createFromSystem(Type type);
    bool loadFromFile(const std::string &path);

    operator SDL_Cursor*() const;

    void apply();

    static void show();
    static void hide();
};

}
