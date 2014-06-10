#include "Animation.h"

namespace KE
{

Animation::Animation(int fps, const std::vector<size_t> &frameIDs)
{
    this->fps = fps;
    this->frameIDs = frameIDs;
}

size_t Animation::getFrameAt(Uint32 time, bool loop, bool backwards) const
{
    size_t frame = time * fps / 1000;

    if (loop)
    {
        frame %= frameIDs.size();
    }
    else if (frame >= frameIDs.size())
    {
        frame = frameIDs.size() - 1;
    }

    if (backwards)
    {
        frame = frameIDs.size() - 1 - frame;
    }

    return frame;
}

}
