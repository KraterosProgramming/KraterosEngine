#include "Sprite.h"
#include "Game.h"

namespace KE
{

Sprite::Sprite(const Tileset *tileset)
{
    this->tileset = tileset;
    this->animation = tileset->getAnimation("idle");
    this->startTime = 0;
    this->pauseTime = 0;
    this->loop = false;
    this->backwards = false;
}

Uint32 Sprite::getCurTime()
{
    if (pauseTime)
    {
        return pauseTime - startTime;
    }
    else
    {
        return Game::getTime() - startTime;
    }
}

size_t Sprite::getCurFrame()
{
    return animation->getFrameAt(getCurTime(), loop, backwards);
}

void Sprite::play(const std::string &animation, bool loop, bool backwards)
{
    startTime = Game::getTime();
    pauseTime = 0;
    this->animation = tileset->getAnimation(animation);
    this->loop = loop;
    this->backwards = backwards;
}

void Sprite::pause()
{
    pauseTime = Game::getTime();
}

void Sprite::resume()
{
    pauseTime = 0;
}

void Sprite::draw(const Point &position)
{
    tileset->draw(position, getCurFrame());
}

}
