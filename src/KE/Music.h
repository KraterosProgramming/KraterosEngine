#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace KE
{

template<class> class Collection;

class Music
{
    Mix_Music *mixMusic;

    void load(Mix_Music *mixMusic);
    void unload();

protected:
    friend class Collection<Music>;
    Music();
    ~Music();

    bool loadFromFile(const std::string &path);

public:
    static std::string getName();

    void play(int fadeInMS = 0);
    void loop(int fadeInMS = 0);

    static void stop(int fadeOutMS = 0);
    static void pause();
    static void resume();
    static void setVolume(int volume);
    static int getVolume();
};

}
