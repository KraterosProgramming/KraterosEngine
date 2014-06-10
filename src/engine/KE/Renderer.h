#pragma once
#include <SDL2/SDL.h>

#include "Window.h"
#include "Color.h"
#include "Texture.h"
#include "Geometry.h"

namespace KE
{

class Renderer
{
    SDL_Renderer *sdlRenderer;
    const Window *window;

    bool setColor(const Color &color);

    void load(SDL_Renderer *sdlRenderer, const Window *window);
    void unload();

protected:
    friend class Game;

    Renderer();

    void quit();

    bool create(const Window &window);

    void present();

public:
    operator SDL_Renderer*() const;

    bool render(const Color &color);
    bool render(const Point &point, const Color &color);
    bool render(const Line &line, const Color &color);
    bool render(const Rect &rect, const Color &color);
    bool renderFill(const Rect &rect, const Color &color);
    bool render(const Texture &texture, const Rect &src, const Rect &dst);

    bool captureScreen();
};

}
