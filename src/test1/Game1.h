#pragma once
#include <KE/KE.h>
using namespace KE;

#include "Scene1.h"

class Game1 : public Game
{
    virtual int onStart() override {
        Log() << "Game1 on start";
        startScene(new Scene1());
        return 0;
    }
    virtual bool onExit()  override {
        Log() << "Game1 on exit";
        return true;
    }

public:
    Game1() : Game(Point(600, 480), "Title") {
        Log() << "new game1";
    }
    virtual ~Game1() {
        Log() << "delete game1";
    }
};
