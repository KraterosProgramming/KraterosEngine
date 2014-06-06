#pragma once
#include <SDL2/SDL.h>

#include "Window.h"
#include "Texture.h"
#include "Geometry.h"

namespace KE
{

class Renderer
{
    SDL_Renderer *sdlRenderer;

    bool setColor(const Color &color);

    void load(SDL_Renderer *sdlRenderer);
    void unload();

protected:
    friend class App;
    friend class Game;

    Renderer();
    ~Renderer();

    operator SDL_Renderer*() const;

    bool create(const Window &window);

    void present();

public:
    bool render(const Color &color);
    bool render(const Point &point, const Color &color);
    bool render(const Line &line, const Color &color);
    bool render(const Rect &rect, const Color &color);
    bool renderFill(const Rect &rect, const Color &color);
    bool render(const Texture &texture, const Rect &src, const Rect &dst);

    bool captureScreen();
};

}
