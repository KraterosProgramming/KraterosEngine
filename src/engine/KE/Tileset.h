#pragma once
#include <map>
#include <string>

#include "Texture.h"
#include "Rect.h"
#include "Animation.h"

namespace KE
{

class Tileset
{
    struct Frame
    {
        Rect source;
        Point offset;
    };

    const Texture *texture;
    std::vector<Frame> frames;
    std::map<std::string, Animation> animations;

public:
    Tileset();
    ~Tileset();

    const Animation *getAnimation(const std::string &animation) const;

    bool loadFromFile(const std::string &path);

    void draw(const Point &position, size_t frame = 0) const;
    void draw(const Point &position, const Rect &bounds, size_t frame = 0) const; // positive position can be outside canvas
};

}
