#pragma once
#include <KE/KE.h>
using namespace KE;

class InputScene : public Scene
{
    bool checkingText;

    virtual void onUpdate() {
        if (Input::getKeyDown(SDL_SCANCODE_TAB)) {
            Log() << "switching mode";
            checkingText = !checkingText;
        }

        if (checkingText) {
            if (Input::textEntered()) {
                Log() << "text \"" << Input::getText() << "\" entered";
            }
        } else {
            for (int k = 0; k < Input::getNumKeys(); ++k) {
                if (Input::getKey(k)) {
                    Log() << "key " << Input::getKeyName(k) << " is being hold";
                }
            }
        }
    }

public:
    InputScene() {
        checkingText = false;
    }
};

