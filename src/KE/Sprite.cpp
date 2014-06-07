#include "Sprite.h"
#include "Tools.h"

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

std::string Sprite::getName()
{
    return "Sprite";
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

}
