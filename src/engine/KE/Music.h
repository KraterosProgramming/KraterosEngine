#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace KE
{

class Music
{
    Mix_Music *mixMusic;

    void load(Mix_Music *mixMusic);
    void unload();

public:
    Music();
    ~Music();

    bool loadFromFile(const std::string &path);

    void play(int fadeInMS = 0);
    void loop(int fadeInMS = 0);

    static void stop(int fadeOutMS = 0);
    static void pause();
    static void resume();
    static void setVolume(int volume);
    static int getVolume();
};

}
