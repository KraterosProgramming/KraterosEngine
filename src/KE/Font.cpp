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

bool Font::renderOnSurface(Surface &out, const std::string &text, const Color &color) const
{
    SDL_Surface* rendered = TTF_RenderText_Solid(sdlFont, (text == "" ? " " : text).c_str(), color);
    if (!rendered)
    {
        Error() << "rendering text \"" << text << "\": " << TTF_GetError();
    }
    else
    {
        out.create(rendered);
    }
    return rendered;
}

bool Font::renderOnTexture(Texture &out, const std::string &text, const Color &color) const
{
    bool ok = false;
    Surface surface;
    if (!renderOnSurface(surface, text, color))
    {
        Error() << "could not render on texture";
    }
    else
    {
        ok = out.loadFromSurface(surface);
    }
    return ok;

}

}
