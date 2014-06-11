#include "Timer.h"
#include "Game.h"

namespace KE
{

Timer::Timer()
{
    this->startTime = 0;
    this->pauseTime = 0;
}

Timer::State Timer::getState()
{
    return state;
}

Uint32 Timer::getTime()
{
    if (state == Stopped)
    {
        return 0;
    }
    else if (state == Paused)
    {
        return pauseTime - startTime;
    }
    else
    {
        return Game::getTime() - startTime;
    }
}

void Timer::start()
{
    state = Started;
    startTime = Game::getTime();
}

void Timer::stop()
{
    state = Stopped;
}

void Timer::pause()
{
    if (state == Started)
    {
        state = Paused;
        pauseTime = Game::getTime();
    }
}

void Timer::resume()
{
    if (state == Paused)
    {
        state = Started;
        startTime += Game::getTime() - pauseTime;
    }
}

bool Timer::every(Uint32 lapse)
{
    if (Game::getTime() == startTime)
    {
        return true;
    }
    if (state != Started || Game::getTime() < startTime + lapse)
    {
        return false;
    }
    else
    {
        startTime += lapse;
        return true;
    }
}

}
