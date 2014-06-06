#include "App.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Tools.h"

namespace KE
{

App::App()
{

}

App::~App()
{
    quit();
}

bool App::init()
{
    bool ok = false;
    Log() << "initiating Krateros Engine...";

    srand(time(nullptr));
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        Error() << "initiating SDL: " << SDL_GetError();
    }
    else
    {
        Log() << "SDL initiated";
        if ((IMG_Init(SUPPORTED_IMAGE_TYPES) & SUPPORTED_IMAGE_TYPES) != SUPPORTED_IMAGE_TYPES)
        {
            Error() << "initiating image support: " << IMG_GetError();
        }
        else
        {
            Log() << "image support initiated";
            if (TTF_Init() < 0)
            {
                Error() << "initiating font support: " << TTF_GetError();
            }
            else
            {
                Log() << "font support initiated";
                if ((Mix_Init(SUPPORTED_AUDIO_TYPES) & SUPPORTED_AUDIO_TYPES) != SUPPORTED_AUDIO_TYPES)
                {
                    Error() << "initiating audio support" << Mix_GetError();
                }
                else
                {
                    Log() << "audio support loaded";
                    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, AUDIO_CHUNK_SIZE) < 0)
                    {
                        Error() << "opening audio: " << Mix_GetError();
                    }
                    else
                    {
                        Log() << "audio opened";
                        if (window.create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE))
                        {
                            if (renderer.create(window))
                            {
                                ok = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ok;
}

void App::quit()
{
    Log() << "closing libraries...";
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}
