#pragma once

#include "Tileset.h"

namespace KE
{

class Sprite
{
    const Tileset *tileset;
    const Animation *animation;
    Uint32 startTime, pauseTime;
    bool loop, backwards;

public:
    Sprite(const Tileset *tileset);

    Uint32 getCurTime();
    size_t getCurFrame();

    void play(const std::string &animation, bool loop, bool backwards);
    void pause();
    void resume();

    void draw(const Point &position);
};

}
