#include "Font.h"
#include <string>

#include "Tools.h"
using namespace tinyxml2;

namespace KE
{

Font::Font()
{
    this->ttfFont = nullptr;
}

Font::~Font()
{
    unload();
}

void Font::load(TTF_Font *ttfFont)
{
    unload();
    this->ttfFont = ttfFont;
}

void Font::unload()
{
    if (ttfFont)
    {
        TTF_CloseFont(ttfFont);
        ttfFont = nullptr;
    }
}

Font::operator TTF_Font*() const
{
    return ttfFont;
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
//    <font file="font.ttf" size="24" />
//    <font file="font.ttf" size="24" style="bold" />
    XMLDocument doc;
    XMLError loaded = doc.LoadFile(path.c_str());
    if (!loaded)
    {
        Error() << "opening XML file \"" << path << "\": XML error = " << loaded;
    }
    else
    {
        const XMLElement *fnt = doc.FirstChildElement("font");
        if (!fnt)
        {
            Error() << "no font element in file \"" << path << "\"";
        }
        else
        {
            const char *file = fnt->Attribute("file");
            int size = fnt->IntAttribute("size");

            TTF_Font *opened = TTF_OpenFont(file, size);
            if (!opened)
            {
                Error() << "could not open TTF font: " << TTF_GetError();
            }
            else
            {
                int style = 0;
                if (fnt->Attribute("style", "bold"))
                {
                    style = Style::Bold;
                }
                else if (fnt->Attribute("style", "italic"))
                {
                    style = Style::Italic;
                }
                else if (fnt->Attribute("style", "underline"))
                {
                    style = Style::Underline;
                }
                else if (fnt->Attribute("style", "strike through"))
                {
                    style = Style::StrikeThrough;
                }

                if (style)
                {
                    TTF_SetFontStyle(ttfFont, style);
                }

                load(ttfFont);
                return true;
            }
        }
    }
    return false;
}

bool Font::renderOnSurface(Surface &out, const std::string &text, const Color &color) const
{
    SDL_Surface* rendered = TTF_RenderText_Solid(ttfFont, (text == "" ? " " : text).c_str(), color);
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
