#include "Color.h"
#include "Tools.h"

namespace KE
{

const Color Color::black(0, 0, 0, 255);
const Color Color::gray(127, 127, 127, 255);
const Color Color::white(255, 255, 255, 255);

const Color Color::red(255, 0, 0, 255);
const Color Color::green(0, 255, 0, 255);
const Color Color::blue(0, 0, 255, 255);

const Color Color::yellow(255, 255, 0, 255);
const Color Color::cyan(0, 255, 255, 255);
const Color Color::magenta(255, 0, 255, 255);

Color::Color()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 255;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::operator SDL_Color()
{
    return *(SDL_Color*)(this);
}

const Color Color::operator+ (const Color &o) const
{
    Uint8 red = std::min<Uint8>(255, r + o.r);
    Uint8 green = std::min<Uint8>(255, g + o.g);
    Uint8 blue = std::min<Uint8>(255, b + o.b);
    Uint8 alpha = std::min<Uint8>(255, a + o.a);
    return Color(red, green, blue, alpha);
}

const Color Color::operator- (const Color &o) const
{
    Uint8 red = std::max<Uint8>(0, r - o.r);
    Uint8 green = std::max<Uint8>(0, g - o.g);
    Uint8 blue = std::max<Uint8>(0, b - o.b);
    Uint8 alpha = std::max<Uint8>(0, a - o.a);
    return Color(red, green, blue, alpha);
}

const Color Color::operator* (float f) const
{
    if (f < 0) f *= -1;

    Uint8 red = std::min<Uint8>(255, r * f);
    Uint8 green = std::min<Uint8>(255, g * f);
    Uint8 blue = std::min<Uint8>(255, b * f);
    Uint8 alpha = std::min<Uint8>(255, a * f);
    return Color(red, green, blue, alpha);
}

const Color Color::operator/ (float f) const
{
    if (f < 0) f *= -1;

    Uint8 red = std::min<Uint8>(255, r / f);
    Uint8 green = std::min<Uint8>(255, g / f);
    Uint8 blue = std::min<Uint8>(255, b / f);
    Uint8 alpha = std::min<Uint8>(255, a / f);
    return Color(red, green, blue, alpha);
}

}
