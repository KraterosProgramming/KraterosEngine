#pragma once

#include "HUDObject.h"
#include "Texture.h"
#include "Font.h"

namespace KE
{

class HUDText : public HUDObject
{
    Texture texture;
    const Font *font;
    std::string text;
    Color color;

protected:
    void renderText();

public:
    HUDText(const Point &position, int z, const Font *font, const std::string &text, const Color &color);

    virtual void onDraw() override;
};

}
