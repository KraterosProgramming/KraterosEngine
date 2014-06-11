#pragma once
#include <KE/KE.h>
using namespace KE;

#include "LibraryScene.h"

class LibraryTest : public Game {
    virtual int onStart() override {
        startScene(new LibraryScene());
        return 0;
    }
public:
    LibraryTest() : Game(Point(800, 400), "Library test") {

    }
};
