#pragma once

#include <KE/KE.h>

class Game : public KE::Game
{
public:
    Game();
    virtual int onStart() override;
    virtual bool onExit()  override;
};
