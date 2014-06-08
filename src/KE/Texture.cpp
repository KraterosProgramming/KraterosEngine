#include "Texture.h"
#include "Tools.h"
#include "Game.h"

namespace KE
{

Texture::Texture()
{
    this->sdlTexture = nullptr;
}

Texture::~Texture()
{
	unload();
}

void Texture::load(SDL_Texture* sdlTexture, const Point &size)
{
    unload();
    this->sdlTexture = sdlTexture;
    this->size = size;
}

void Texture::unload()
{
    if (sdlTexture)
    {
        SDL_DestroyTexture(sdlTexture);
        sdlTexture = nullptr;
        size = Point(0, 0);
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
        load(created, surface.getSize());
    }
    return created;
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

const Point Texture::getSize() const
{
    return size;
}

const Rect Texture::getClip() const
{
    return Rect().grow(size);
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
