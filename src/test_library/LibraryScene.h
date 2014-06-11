#pragma once
#include <KE/KE.h>
using namespace KE;

class LibraryScene : public Scene {
    const Tileset *tileset;
    const Sound *sound;
    Point position;
    Timer timer;
    Sprite sprite;

    const Uint32 lapse = 1000;

    virtual void onStart() override {
        tileset = Library::getTileset("character");
        sound = Library::getSound("moonCricket");

        sprite.setTileset(Library::getTileset("fire"));
        sprite.play("idle", true);
        sprite.pause();

        Library::getCursor("frostSwordAx")->apply();
        Library::getMusic("keygen")->loop(500);

        Music::setVolume(64);

        position = Game::getWindowSize() / 2;
    }

    virtual void onUpdate() override {
        if (Input::getButtonDown(SDL_BUTTON_LMASK)) {
            timer.start();
            sprite.resume();
            Library::getCursor("fireWarHammer")->apply();
        }

        if (Input::getButtonUp(SDL_BUTTON_LMASK)) {
            timer.stop();
            sprite.pause();
            Library::getCursor("frostSwordAx")->apply();
        }

        if (Input::getButton(SDL_BUTTON_LMASK)) {
            position = Input::getMouse();
        }

        if (timer.every(lapse)) {
            sound->play();
        }
    }

    virtual void onDraw() override {
        tileset->draw(Game::getWindowSize() / 2);
        sprite.draw(position);
    }

public:
    LibraryScene() {
        this->tileset = nullptr;
        this->sound = nullptr;
    }
};
