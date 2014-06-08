#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace KE
{

template<class> class Collection;

class Sound
{
    Mix_Chunk *mixChunk;

    void load(Mix_Chunk *mixChunk);
    void unload();

public:
    Sound();
    ~Sound();

    bool loadFromFile(const std::string &path);

    void play(int channel, int fadeInMS = 0);
    void loop(int channel, int fadeInMS = 0);

    static void stop(int channel, int fadeOutMS = 0);
    static void pause(int channel);
    static void resume(int channel);

    static void setVolume(int channel, int volume);
    static int getVolume(int channel);
};

}
