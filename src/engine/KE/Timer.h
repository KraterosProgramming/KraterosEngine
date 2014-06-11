#pragma once
#include <SDL2/SDL.h>

namespace KE
{

class Timer
{
public:
    enum State
    {
        Stopped,
        Started,
        Paused
    };

private:
    State state;
    Uint32 startTime;
    Uint32 pauseTime;

public:
    Timer();

    State getState();
    Uint32 getTime();

    void start();
    void stop();

    void pause();
    void resume();

    bool every(Uint32 lapse);
};

}
