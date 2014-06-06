#include "Font.h"
#include <string>
#include "Tools.h"

namespace KE
{

Font::Font()
{
    this->sdlFont = nullptr;
}

Font::~Font()
{
    unload();
}

void Font::load(TTF_Font *sdlFont)
{
    unload();
    this->sdlFont = sdlFont;
}

void Font::unload()
{
    if (sdlFont)
    {
        TTF_CloseFont(sdlFont);
        sdlFont = nullptr;
    }
}

Font::operator TTF_Font*() const
{
    return sdlFont;
}

bool Font::loadFromFile(const std::string &path, int size, int style)
{
    TTF_Font *loaded = TTF_OpenFont(path.c_str(), size);
    if (!loaded)
    {
        Error() << "opening font: " << TTF_GetError();
    }
    else
    {
        if (style)
        {
            TTF_SetFontStyle(loaded, style);
        }
        load(loaded);
    }
    return loaded;
}

bool Font::loadFromFile(const std::string &path)
{
    // TODO: font definition in XML file
    return false;
}

SDL_Surface* Font::renderText(const std::string &text, const Color &color)
{
    SDL_Surface* rendered = TTF_RenderText_Solid(sdlFont, (text == "" ? " " : text).c_str(), color);
    if (!rendered)
    {
        Error() << "rendering text \"" << text << "\": " << TTF_GetError();
    }
    return rendered;
}

bool Font::renderLines(const std::string &text, const Color &color, std::vector<SDL_Surface*> vec)
{
    bool ok = true;
    std::string::size_type begin = 0, end = 0;
    std::string line = "";

    while (begin != text.size())
    {
        end = text.find_first_of('\n', begin);
        line = text.substr(begin, end);
        SDL_Surface* surface = renderText(line, color);
        if (!surface)
        {
            ok = false;
        }
        else
        {
            vec.push_back(surface);
        }
    }
    return ok;
}

std::string Font::getName()
{
    return "Font";
}

}
