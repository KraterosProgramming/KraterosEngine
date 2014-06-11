#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace KE
{

class Sound
{
    Mix_Chunk *mixChunk;

    void load(Mix_Chunk *mixChunk);
    void unload();

public:
    Sound();
    ~Sound();

    bool loadFromFile(const std::string &path);

    void play(int channel = -1, int fadeInMS = 0) const;
    void loop(int channel = -1, int fadeInMS = 0) const;

    static void stop(int channel = -1, int fadeOutMS = 0);
    static void pause(int channel = -1);
    static void resume(int channel = -1);

    static void setVolume(int volume, int channel = -1);
    static int getVolume(int channel = -1);
};

}
