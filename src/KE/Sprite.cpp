#include "Sprite.h"
#include "Tools.h"
#include "Geometry.h"

namespace KE
{

Sprite::Sprite()
{
    this->texture = nullptr;
}

Sprite::~Sprite()
{

}

bool Sprite::loadFromFile(const std::string &path)
{
    // TODO: load sprite from XML
    return false;
}

void Sprite::draw(const Point &position, size_t frame)
{
    if (!texture)
    {
        Error() << "no texture associated to this sprite.";
    }
    else if (frame >= frames.size())
    {
        Error() << "trying to render frame number " << frame << " from " << frames.size() << " frames.";
    }
    else
    {
        texture->draw(position, frames[frame]);
    }
}

void Sprite::draw(const Point &position, const Rect &canvas, size_t frame)
{
    if (!texture)
    {
        Error() << "no texture associated to this sprite.";
    }
    else if (frame >= frames.size())
    {
        Error() << "trying to render frame number " << frame << " from " << frames.size() << " frames.";
    }
    else
    {
        Point final_position (std::max(position.x, canvas.x), std::max(position.y, canvas.y));
        Rect final_source = Geometry::intersect(frames[frame], canvas.move(-position));
        texture->draw(final_position, final_source);
    }
}

}
