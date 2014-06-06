#pragma once
#include <SDL2/SDL.h>

namespace KE
{

class Color : public SDL_Color
{
public:
    static const Color black;
    static const Color gray;
    static const Color white;

    static const Color red;
    static const Color green;
    static const Color blue;

    static const Color yellow;
    static const Color cyan;
    static const Color magenta;

    Color();
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    operator SDL_Color();

    const Color operator+ (const Color &o) const;
    const Color operator- (const Color &o) const;
    const Color operator* (float f) const;
    const Color operator/ (float f) const;
};

}
