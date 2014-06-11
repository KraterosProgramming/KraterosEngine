#pragma once

#include "Tileset.h"
#include "Timer.h"

namespace KE
{

class Sprite
{
    const Tileset *tileset;
    const Animation *animation;
    Timer timer;
    bool loop, backwards;

public:
    Sprite();

    void setTileset(const Tileset *tileset);
    size_t getCurFrame();

    void play(const std::string &animation = "idle", bool loop = false, bool backwards = false);
    void pause();
    void resume();

    void draw(const Point &position);
};

}
