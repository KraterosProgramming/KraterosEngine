#include "Font.h"
#include <string>

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
//    <font file="font.ttf" size="24" style="b" />

    bool ok = false;

    XMLDocument doc;
    XMLError error = doc.LoadFile(path.c_str());
    if (error != XML_NO_ERROR)
    {
        Error() << "opening font file \"" << path << "\": XML error = " << error;
    }
    else
    {
        const XMLElement *elem = doc.FirstChildElement("font");
        if (!elem)
        {
            Error() << "no font element in file \"" << path << "\"";
        }
        else
        {
            const char *fileAttr = elem->Attribute("file");
            if (!fileAttr)
            {
                Error() << "no file attribute in font element, in file \"" << path << "\"";
            }
            else
            {
                int size = elem->IntAttribute("size");
                if (!size)
                {
                    Error() << "no size attribute in font element, in file \"" << path << "\"";
                }
                else
                {
                    int style = 0;

                    // optional style
                    const char* styleDesc = elem->Attribute("style");
                    if (styleDesc)
                    {
                        for (const char* c = styleDesc; *c != '\0'; ++c)
                        {
                            switch (*c)
                            {
                                case 'b':   style |= TTF_STYLE_BOLD;            break;
                                case 'i':   style |= TTF_STYLE_ITALIC;          break;
                                case 's':   style |= TTF_STYLE_STRIKETHROUGH;   break;
                                case 'u':   style |= TTF_STYLE_UNDERLINE;       break;
                            }
                        }
                    }

                    std::string file = path.substr(0, path.find_last_of('/') + 1) + fileAttr;
                    ok = loadFromFile(file, size, style);
                }
            }
        }
    }

    return ok;
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
