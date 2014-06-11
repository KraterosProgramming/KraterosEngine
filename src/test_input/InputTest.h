#pragma once
#include <KE/KE.h>
using namespace KE;

class InputTest : public Game {
    virtual int onStart() override {
        startScene(new InputScene());
        return 0;
    }
public:
    InputTest() : Game(Point(800, 400), "Input test") { }
};
