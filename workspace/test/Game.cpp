#include "Game.h"

Game::Game() : KE::Game(800, 500, "Hello World")
{

}

void Game::onStart()
{
    KE::Log() << "yay";
}

void Game::onExit()
{
    KE::Log() << "lol";
}
