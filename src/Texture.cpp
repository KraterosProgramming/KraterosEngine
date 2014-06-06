#include "Texture.h"
#include "Tools.h"
#include "Game.h"

namespace KE
{

Texture::Texture()
{
    this->sdlTexture = nullptr;
    this->w = 0;
    this->h = 0;
}

Texture::~Texture()
{
	unload();
}

void Texture::load(SDL_Texture* sdlTexture, int w, int h)
{
    unload();
    this->sdlTexture = sdlTexture;
    this->w = w;
    this->h = h;
}

void Texture::unload()
{
    if (sdlTexture)
    {
        SDL_DestroyTexture(sdlTexture);
        sdlTexture = nullptr;
        w = 0;
        h = 0;
    }
}

Texture::operator SDL_Texture*() const
{
    return sdlTexture;
}

bool Texture::loadFromSurface(const Surface &surface)
{
    // TODO: reference to renderer
    SDL_Texture *created = SDL_CreateTextureFromSurface(nullptr, surface);
    if (!created)
    {
        Error() << "creating texture from surface: " << SDL_GetError();
    }
    else
    {
        load(created, surface.getWidth(), surface.getHeight());
    }
    return created;
}

bool Texture::loadFromSurfaceVec(const std::vector<Surface> &surfaces)
{
    bool loaded = false;
    int w = 0, h = 0;
    for (auto &surface : surfaces)
    {
        w = std::max(w, surface.getWidth());
        h += surface.getHeight();
    }

    Surface made;
    if (made.create(w, h, surfaces[0].getFormat()))
    {
        Rect rect(0, 0, w, 0);
        for (auto &surface : surfaces)
        {
            rect.h = surface.getHeight();
            if (surface.blit(made, rect))
            {
                rect.y += rect.h;
            }
        }

        loaded = loadFromSurface(made);
    }
    return loaded;
}

bool Texture::loadFromFile(const std::string &path)
{
    bool loaded = false;
    Surface surface;
    if (surface.loadFromFile(path.c_str()))
    {
        loaded = loadFromSurface(surface);
    }
    return loaded;
}

bool Texture::renderText(const Font &font, const std::string &text, const Color &color)
{
    bool loaded = false;
    Surface rendered;
    if (rendered.renderText(font, text, color))
    {
        loaded = loadFromSurface(rendered);
    }
    return loaded;
}

std::string Texture::getName()
{
    return "Texture";
}

void Texture::draw(const Point &position, const Rect &source) const
{
    Game::getRenderer().render(*this, source, source.move(position));
}

}
