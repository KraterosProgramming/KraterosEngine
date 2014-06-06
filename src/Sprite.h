#pragma once

#include "Texture.h"
#include "Rect.h"

namespace KE
{

template<class> class Collection;

class Sprite
{
    const Texture* texture;
    std::vector<Rect> frames;

protected:
    friend class Collection<Sprite>;
    Sprite();
    ~Sprite();

    bool loadFromFile(const std::string &path);

public:
    static std::string getName();

    void draw(const Point &position, size_t frame = 0);
};

}
