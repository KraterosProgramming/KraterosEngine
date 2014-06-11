#include "Sprite.h"
#include "Game.h"

namespace KE
{

Sprite::Sprite()
{
    this->tileset = nullptr;
    this->animation = nullptr;
    this->loop = false;
    this->backwards = false;
}

void Sprite::setTileset(const Tileset *tileset)
{
    this->tileset = tileset;
    this->animation = tileset->getAnimation("idle");
}

size_t Sprite::getCurFrame()
{
    return animation->getFrameAt(timer.getTime(), loop, backwards);
}

void Sprite::play(const std::string &animation, bool loop, bool backwards)
{
    timer.start();

    this->animation = tileset->getAnimation(animation);
    this->loop = loop;
    this->backwards = backwards;
}

void Sprite::pause()
{
    timer.pause();
}

void Sprite::resume()
{
    timer.resume();
}

void Sprite::draw(const Point &position)
{
    tileset->draw(position, getCurFrame());
}

}
