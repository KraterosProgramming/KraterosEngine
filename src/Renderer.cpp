#include "Renderer.h"
#include "Game.h"
#include "Tools.h"

namespace KE
{

Renderer::Renderer()
{
    this->sdlRenderer = nullptr;
}

Renderer::~Renderer()
{
    unload();
}

void Renderer::load(SDL_Renderer *sdlRenderer)
{
    this->sdlRenderer = sdlRenderer;
}

void Renderer::unload()
{
    if (sdlRenderer)
    {
        SDL_DestroyRenderer(sdlRenderer);
        sdlRenderer = nullptr;
    }
}

Renderer::operator SDL_Renderer*() const
{
    return sdlRenderer;
}

bool Renderer::setColor(const Color &color)
{
    if (SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a) < 0)
    {
        Error() << "setting draw color for render: " << SDL_GetError();
    }
    else
    {
        return true;
    }
    return false;
}

bool Renderer::create(const Window &window)
{
    SDL_Renderer *created = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (!created)
    {
        Error() << "creating renderer: " << SDL_GetError();
    }
    else
    {
        load(created);
    }
    return created;
}

void Renderer::present()
{
    SDL_RenderPresent(sdlRenderer);
}

bool Renderer::render(const Color &color)
{
    if ((!setColor(color)) || (SDL_RenderClear(sdlRenderer)))
    {
        Error() << "rendering color: " << SDL_GetError();
    }
    else
    {
        return true;
    }
    return false;
}

bool Renderer::render(const Point &point, const Color &color)
{
    if ((!setColor(color)) || (SDL_RenderDrawPoint(sdlRenderer, point.x, point.y) < 0))
    {
        Error() << "rendering point: " << SDL_GetError();
    }
    else
    {
        return true;
    }
    return false;
}

bool Renderer::render(const Line &line, const Color &color)
{
    if ((!setColor(color)) || (SDL_RenderDrawLine(sdlRenderer, line.a.x, line.a.y, line.b.x, line.b.y) < 0))
    {
        Error() << "rendering line: " << SDL_GetError();
    }
    else
    {
        return true;
    }
    return false;
}

bool Renderer::render(const Rect &rect, const Color &color)
{
    if ((!setColor(color)) || (SDL_RenderDrawRect(sdlRenderer, rect) < 0))
    {
        Error() << "rendering rectangle: " << SDL_GetError();
    }
    else
    {
        return true;
    }
    return false;
}

bool Renderer::renderFill(const Rect &rect, const Color &color)
{
    if ((!setColor(color)) || (SDL_RenderFillRect(sdlRenderer, rect) < 0))
    {
        Error() << "rendering rectangle (filled): " << SDL_GetError();
    }
    else
    {
        return true;
    }
    return false;
}

bool Renderer::render(const Texture &texture, const Rect &source, const Rect &destiny)
{
    if (SDL_RenderCopy(sdlRenderer, texture, source, destiny) < 0)
    {
        Error() << "rendering texture: " << SDL_GetError();
    }
    else
    {
        return true;
    }
    return false;
}

bool Renderer::captureScreen()
{
    int w = WINDOW_WIDTH;
    int h = WINDOW_HEIGHT;

    char pixels[w * h * 3];
    if (SDL_RenderReadPixels(Game::getRenderer(), NULL, 0, pixels, 3*w) < 0)
    {
        Error() << "reading screen pixels: " << SDL_GetError();
    }
    else
    {
        Surface screen;
        if (!screen.create(w, h, 24, pixels))
        {
            Error() << "taking a screen shot: " << SDL_GetError();
        }
        else
        {
            time_t now = time(nullptr);

            char fileName[255];
            strftime(fileName, 255, "screenshots/%Y_%m_%d__%H_%M_%S.bmp", localtime(&now));

            if (SDL_SaveBMP(screen, fileName) < 0)
            {
                Error() << "saving screen shot: " << SDL_GetError();
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

}
