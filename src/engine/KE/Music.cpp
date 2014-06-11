#include "Music.h"
#include "Tools.h"

namespace KE
{


Music::Music()
{
    this->mixMusic = nullptr;
}

Music::~Music()
{
    unload();
}

void Music::load(Mix_Music* mixMusic)
{
    unload();
    this->mixMusic = mixMusic;
}

void Music::unload()
{
    if (mixMusic)
    {
        Mix_FreeMusic(mixMusic);
        mixMusic = nullptr;
    }
}

bool Music::loadFromFile(const std::string &path)
{
    Mix_Music *loaded = Mix_LoadMUS(path.c_str());
    if (!loaded)
    {
        Error() << "loading music from file: " << Mix_GetError();
    }
    else
    {
        load(loaded);
    }
    return loaded;
}

void Music::play(int fadeInMS) const
{
    if (!fadeInMS)
    {
        Mix_PlayMusic(mixMusic, 0);
    }
    else
    {
        Mix_FadeInMusic(mixMusic, 0, fadeInMS);
    }
}

void Music::loop(int fadeInMS) const
{
    stop();
    if (!fadeInMS)
    {
        Mix_PlayMusic(mixMusic, -1);
    }
    else
    {
        Mix_FadeInMusic(mixMusic, -1, fadeInMS);
    }
}

void Music::stop(int fadeOutMS)
{
    if (!fadeOutMS)
    {
        Mix_HaltMusic();
    }
    else
    {
        Mix_FadeOutMusic(fadeOutMS);
    }
}

void Music::pause()
{
    Mix_PauseMusic();
}

void Music::resume()
{
    Mix_ResumeMusic();
}

void Music::setVolume(int volume)
{
    Mix_VolumeMusic(std::min(std::max(0, volume), MIX_MAX_VOLUME));
}

int Music::getVolume()
{
    return Mix_VolumeMusic(-1);
}

}
