#include "Game.h"
#include "Scene1.h"

Game::Game() : KE::Game(KE::Point(800, 500), "Hello World")
{

}

int Game::onStart()
{
    KE::Log() << "yay";
    startScene(new Scene1());
    return 0;
}

bool Game::onExit()
{
    KE::Log() << "lol";
    return true;
}
