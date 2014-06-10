#include "HUDText.h"

namespace KE
{

HUDText::HUDText(const Point &position, int z, const Font *font, const std::string &text, const Color &color)
        :HUDObject(position, z)
{
    this->font = font;
    this->text = text;
    this->color = color;
}

void HUDText::renderText()
{
    font->renderOnTexture(texture, text, color);
}

void HUDText::onDraw()
{
    texture.draw(getPosition(), texture.getClip());
}

}
