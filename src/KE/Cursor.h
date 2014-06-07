#pragma once
#include <SDL2/SDL.h>

#include "Surface.h"
#include "Point.h"

namespace KE
{

template<class> class Collection;

class Cursor
{
public:
    using Type = SDL_SystemCursor;

private:
    SDL_Cursor* sdlCursor;

    void load(SDL_Cursor* sdlCursor);
    void unload();

protected:
    friend class Collection<Cursor>;
    Cursor();
    ~Cursor();

    // TODO: create cursor?
    //bool create(int w, int h, const SDL_PixelFormat* format);
    //bool create(int w, int h, int depth, char* pixels);
    bool createFromSurface(const Surface &surface, const Point &p);
    bool createFromSystem(Type type);
    bool loadFromFile(const std::string &path);

public:
    static std::string getName();

    operator SDL_Cursor*() const;

    void apply();

    static void show();
    static void hide();
};

}
