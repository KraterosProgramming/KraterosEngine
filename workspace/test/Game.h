#pragma once

#include <KE/KE.h>

class Game : public KE::Game
{
public:
    Game();
    virtual void onStart() override;
    virtual void onExit()  override;
};
