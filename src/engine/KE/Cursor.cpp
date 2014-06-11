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
//    <cursor file="cursor.png">
//        <point x="0" y="0"/>
//    </cursor>

    bool ok = false;

    XMLDocument doc;
    XMLError error = doc.LoadFile(path.c_str());
    if (error != XML_NO_ERROR)
    {
        Error() << "opening cursor file \"" << path << "\": XML error = " << error;
    }
    else
    {
        const XMLElement *elem = doc.FirstChildElement("cursor");
        if (!elem)
        {
            Error() << "no cursor element in file \"" << path << "\"";
        }
        else
        {
            const char *fileName = elem->Attribute("file");
            if (!fileName)
            {
                Error() << "no file attribute in cursor element, in file \"" << path << "\"";
            }
            else
            {
                // TODO: Path class? getDirectory, getName, getFullPath, concatenating "/"
                std::string file = path.substr(0, path.find_last_of('/') + 1) + fileName;
                ok = loadFromFile(file, Point::parseXML(elem));
            }
        }
    }

    return ok;
}

bool Cursor::loadFromFile(const std::string &path, const Point &p)
{
    Surface surface;
    if (!surface.loadFromFile(path))
    {
        Error() << "could not load cursor image";
    }
    else
    {
        return createFromSurface(surface, p);
    }
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
