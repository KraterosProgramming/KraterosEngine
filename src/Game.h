#pragma once

#include "Scene.h"
#include "App.h"

namespace KE
{

class Game
{
    App app;
    Scene *scene;       // TODO: support multiple scenes at background
    bool mustQuit;
    int result;

    static Game game;


protected:
    Game();
    virtual ~Game();

public:
    int getResult();

    static Object *findObject(const std::string &keyname);

    static void startScene(Scene *scene);
    static void combineScene(Scene *scene);

    static void start();
    static void exit();

    static Window &getWindow();
    static Renderer &getRenderer();
};

}
