#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Tools.h"

namespace KE
{

Game *Game::game = nullptr;
const int Game::defaultAudioFrequency = 44100;
const int Game::defaultAudioChunkSize = 1024;

Game::Game(const Point &startingSize, const std::string &title, int audioFrequency, int audioChunkSize)
{
    this->startingSize = startingSize;
    this->title = title;
    this->audioFrequency = audioFrequency;
    this->audioChunkSize = audioChunkSize;

    this->scene = nullptr;
    this->mustQuit = false;
    this->result = -1;

    if (game)
    {
        delete game;
    }
    game = this;
}

Game::Game(const Point &startingSize, const std::string &title)
{
    this->startingSize = startingSize;
    this->title = title;
    this->audioFrequency = defaultAudioFrequency;
    this->audioChunkSize = defaultAudioChunkSize;

    this->scene = nullptr;
    this->mustQuit = false;
    this->result = -1;

    if (game)
    {
        delete game;
    }
    game = this;
}

Game::~Game()
{
    quit();
    Log() << "closing game";
}

int Game::getResult()
{
    return game->result;
}

const Point Game::getWindowSize()
{
    return game->window.getSize();
}

void Game::setWindowSize(const Point &size)
{
    game->window.setSize(size);
    game->scene->arrange();
}

Renderer &Game::getRenderer()
{
    return game->renderer;
}

bool Game::init()
{
    Log() << "initiating Krateros Engine...";
    srand(time(nullptr));
    if (SDL_Init(INITIATED_SUBSYSTEMS) < 0)
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
                    if (Mix_OpenAudio(audioFrequency, AUDIO_FORMAT, 2, audioChunkSize) < 0)
                    {
                        Error() << "opening audio: " << Mix_GetError();
                    }
                    else
                    {
                        Log() << "audio opened";
                        if (!window.create(startingSize.x, startingSize.y, title))
                        {
                            Error() << "creating window " << startingSize.x << "x" << startingSize.y << ": " << SDL_GetError();
                        }
                        else
                        {
                            Log() << "window created";
                            if (!renderer.create(window))
                            {
                                Error() << "creating renderer: " << SDL_GetError();
                            }
                            else
                            {
                                result = onStart();
                            }
                        }
                    }
                }
            }
        }
    }

    return result == 0;
}

void Game::quit()
{
    if (scene)
    {
        delete scene;
        scene = nullptr;
    }

    Log() << "closing dynamic libraries...";
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::loop()
{
    while (!mustQuit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    exit();
                }
                break;
            }
        }

        renderer.render(Color::red);
        renderer.present();
    }
}

void Game::start()
{
    if (!init())
    {
        Error() << "could not initiate game; quiting now";
    }
    else
    {
        loop();
    }
}

void Game::exit()
{
    game->mustQuit = game->onExit();
}

void Game::exit(int errorCode)
{
    game->result = errorCode;
    game->mustQuit = game->onExit();
}

void Game::add(Object* o)
{
    game->scene->add(o);
}

Object *Game::findObject(const std::string &keyname)
{
	return game->scene->findObject(keyname);
}

void Game::startScene(Scene *scene)
{
    if (game->scene)
    {
        scene->close();
        delete game->scene;
    }
    game->scene = scene;
    scene->start();
}

void Game::combineScene(Scene *scene)
{
    if (!game->scene)
    {
        Warning() << "can not combine to inexistent scene";
    }
    else
    {
        game->scene->transferTo(*scene);
        delete game->scene;
    }
    game->scene = scene;
}

}
