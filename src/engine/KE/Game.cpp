#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Library.h"
#include "Input.h"
#include "Tools.h"

namespace KE
{

Game *Game::game = nullptr;

const int Game::subsystems = SDL_INIT_EVERYTHING;
const int Game::imageTypesSupport = IMG_INIT_JPG|IMG_INIT_PNG;
const int Game::audioTypesSupport = MIX_INIT_OGG;
const int Game::audioFormat = MIX_DEFAULT_FORMAT;

const int Game::defaultAudioFrequency = 44100;
const int Game::defaultAudioChunkSize = 1024;
const int Game::defaultAudioChannels = 16;

const char *Game::defaultTexturesDir = "library/textures/";
const char *Game::defaultTilesetsDir = "library/tilesets/";
const char *Game::defaultCursorsDir = "library/cursors/";
const char *Game::defaultMusicsDir = "library/musics/";
const char *Game::defaultSoundsDir = "library/sounds/";
const char *Game::defaultFontsDir = "library/fonts/";

Game::Game(const Point &startingSize, const std::string &title)
{
    this->startingSize = startingSize;
    this->title = title;

    this->audioFrequency = defaultAudioFrequency;
    this->audioChunkSize = defaultAudioChunkSize;
    this->audioChannels = defaultAudioChannels;

    this->texturesDir = defaultTexturesDir;
	this->tilesetsDir = defaultTilesetsDir;
	this->cursorsDir = defaultCursorsDir;
	this->musicsDir = defaultMusicsDir;
	this->soundsDir = defaultSoundsDir;
	this->fontsDir = defaultFontsDir;

    this->scene = nullptr;
    this->mustQuit = false;
    this->result = -1;
    this->ticks = 0;
    this->deltaTime = 0;

    if (game)
    {
        delete game;
        game = nullptr;
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

Uint32 Game::getTime()
{
    return game->ticks;
}

float Game::getDeltaTime()
{
    return game->deltaTime;
}

const Point Game::getWindowSize()
{
    return game->window.getSize();
}

void Game::setWindowSize(const Point &size)
{
    game->window.setSize(size);
    if (game->scene)
    {
        game->scene->arrange();
    }
}

Window &Game::getWindow()
{
    return game->window;
}

Renderer &Game::getRenderer()
{
    return game->renderer;
}

bool Game::init()
{
    Log() << "initiating Krateros Engine...";
    srand(time(nullptr));
    if (SDL_Init(subsystems) < 0)
    {
        Error() << "initiating SDL: " << SDL_GetError();
    }
    else
    {
        Log() << "SDL initiated";
        if ((IMG_Init(imageTypesSupport) & imageTypesSupport) != imageTypesSupport)
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
                if ((Mix_Init(audioTypesSupport) & audioTypesSupport) != audioTypesSupport)
                {
                    Error() << "initiating audio support" << Mix_GetError();
                }
                else
                {
                    Log() << "audio support loaded";
                    if (Mix_OpenAudio(audioFrequency, audioFormat, 2, audioChunkSize) < 0)
                    {
                        Error() << "opening audio: " << Mix_GetError();
                    }
                    else
                    {
                        Log() << "audio opened";
                        if (Mix_AllocateChannels(audioChannels) < audioChannels)
                        {
                            Error() << "could not allocate " << audioChannels << " audio channels";
                        }
                        else
                        {
                            Log() << "audio channels allocated";
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
                                    Log() << "loading library";
                                    bool libraryOK = Library::loadTextures(texturesDir) &&
                                                     Library::loadTilesets(tilesetsDir) &&
                                                     Library::loadCursors(cursorsDir) &&
                                                     Library::loadMusics(musicsDir) &&
                                                     Library::loadSounds(soundsDir) &&
                                                     Library::loadFonts(fontsDir);
                                    if (!libraryOK)
                                    {
                                        Error() << "could not load library";
                                    }
                                    else
                                    {
                                        Input::start();

                                        result = onStart();
                                    }
                                }
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

    Library::quit();
    Input::quit();

    renderer.quit();
    window.quit();

    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    Log() << "dynamic libraries closed";
}

void Game::loop()
{
    ticks = SDL_GetTicks();
    while (!mustQuit)
    {
        Uint32 newTicks = SDL_GetTicks();
        deltaTime = 0.001f * (newTicks - ticks);
        ticks = newTicks;

        Input::update();

        if (!scene)
        {
            Warning() << "no scene created";
        }
        else
        {
            scene->think();
            scene->update();
        }

        renderer.render(Color::green);
        if (scene)
        {
            scene->draw();
        }
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
    if (game->scene)
    {
        game->scene->close();
    }
}

void Game::exit(int errorCode)
{
    game->result = errorCode;
    game->mustQuit = game->onExit();
    if (game->scene)
    {
        game->scene->close();
    }
}

void Game::startScene(Scene *scene)
{
    if (game->scene)
    {
        scene->close();
        delete game->scene;
        game->scene = nullptr;
    }
    game->scene = scene;
    scene->start();
    scene->arrange();
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
        game->scene = nullptr;
    }
    game->scene = scene;
    game->scene->start();
    game->scene->arrange();
}

}
