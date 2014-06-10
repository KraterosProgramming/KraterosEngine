#include "Cursor.h"
#include "Tools.h"

namespace KE
{

Cursor::Cursor()
{
    this->sdlCursor = nullptr;
}

Cursor::~Cursor()
{
    unload();
}

void Cursor::load(SDL_Cursor* sdlCursor)
{
    unload();
    this->sdlCursor = sdlCursor;
}

void Cursor::unload()
{
    if (this->sdlCursor)
    {
        SDL_FreeCursor(sdlCursor);
        sdlCursor = nullptr;
    }
}

bool Cursor::createFromSurface(const Surface &surface, const Point &p)
{
    SDL_Cursor *created = SDL_CreateColorCursor(surface, p.x, p.y);
    if (!created)
    {
        Error() << "creating cursor from surface: " << SDL_GetError();
    }
    else
    {
        load(created);
    }
    return created;
}

bool Cursor::createFromSystem(Type type)
{
    SDL_Cursor *created = SDL_CreateSystemCursor(type);
    if (!created)
    {
        Error() << "creating cursor from system: " << SDL_GetError();
    }
    else
    {
        load(created);
    }
    return created;
}

bool Cursor::loadFromFile(const std::string &path)
{
    // TODO: load cursor from XML
    return false;
}

std::string Cursor::getName()
{
    return "Cursor";
}

Cursor::operator SDL_Cursor*() const
{
    return sdlCursor;
}

void Cursor::show()
{
    if (SDL_ShowCursor(1) < 0)
    {
        Error() << "showing the cursor: " << SDL_GetError();
    }
}

void Cursor::hide()
{
    if (SDL_ShowCursor(0) < 0)
    {
        Error() << "hiding the cursor: " << SDL_GetError();
    }
}

void Cursor::apply()
{
    SDL_SetCursor(sdlCursor);
}

}
