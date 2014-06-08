#pragma once

#include "Texture.h"
#include "Rect.h"

namespace KE
{

class Sprite
{
    const Texture* texture;
    std::vector<Rect> frames;

public:
    Sprite();
    ~Sprite();

    bool loadFromFile(const std::string &path);

    void draw(const Point &position, size_t frame = 0);
    void draw(const Point &position, const Rect &canvas, size_t frame = 0); // positive position can be outside canvas
};

}
