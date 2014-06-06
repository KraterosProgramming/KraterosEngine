#include "Game.h"
#include "App.h"

namespace KE
{

Game Game::game;

Game::Game()
{
    this->scene = nullptr;
    this->mustQuit = false;
    this->result = 0;
}

Game::~Game()
{
    app.quit();
}

int Game::getResult()
{
    return result;
}

Window &Game::getWindow()
{
    return game.app.window;
}

Renderer &Game::getRenderer()
{
    return game.app.renderer;
}

Object *Game::findObject(const std::string &keyname)
{
	return game.scene->findObject(keyname);
}

void Game::startScene(Scene *scene)
{

}

void Game::combineScene(Scene *scene)
{

}

void Game::start()
{
    if (game.app.init())
    {
        while (!game.mustQuit)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    game.mustQuit = true;
                }
            }

            game.app.renderer.render(Color::red);
            game.app.renderer.present();
        }
    }
}

void Game::exit()
{
    game.mustQuit = true;
}

}
