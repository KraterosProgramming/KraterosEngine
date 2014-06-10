#pragma once
#include <vector>

#include <SDL2/SDL.h>

namespace KE
{

class Animation
{
    int fps;
    std::vector<size_t> frameIDs;

public:
    Animation(int fps, const std::vector<size_t> &frameIDs);

    size_t getFrameAt(Uint32 time, bool loop, bool backwards) const;
};

}
