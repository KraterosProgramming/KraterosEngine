#include "Sound.h"
#include "Tools.h"

namespace KE
{


Sound::Sound()
{
    this->mixChunk = nullptr;
}

Sound::~Sound()
{
    unload();
}

void Sound::load(Mix_Chunk* mixChunk)
{
    unload();
    this->mixChunk = mixChunk;
}

void Sound::unload()
{
    if (mixChunk)
    {
        Mix_FreeChunk(mixChunk);
        mixChunk = nullptr;
    }
}

bool Sound::loadFromFile(const std::string &path)
{
    Mix_Chunk *loaded = Mix_LoadWAV(path.c_str());
    if (!loaded)
    {
        Error() << "loading sound from file: " << Mix_GetError();
    }
    else
    {
        load(loaded);
    }
    return loaded;
}

std::string Sound::getName()
{
    return "Sound";
}

void Sound::play(int channel, int fadeInMS)
{
     Mix_FadeInChannel(channel, mixChunk, 0, fadeInMS);
}

void Sound::loop(int channel, int fadeInMS)
{
    Mix_FadeInChannel(channel, mixChunk, -1, fadeInMS);
}

void Sound::stop(int channel, int fadeOutMS)
{
    Mix_FadeOutChannel(channel, fadeOutMS);
}

void Sound::pause(int channel)
{
    Mix_Pause(channel);
}

void Sound::resume(int channel)
{
    Mix_Resume(channel);
}

void Sound::setVolume(int channel, int volume)
{
    Mix_Volume(channel, std::min(std::max(0, volume), MIX_MAX_VOLUME));
}

int Sound::getVolume(int channel)
{
    return Mix_Volume(channel, -1);
}

}
