#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "Point.h"

namespace KE
{

class Input
{
public:
    static const size_t maxJoysticks;

private:
    int numKeys;
    const Uint8 *keyboard;
    Uint8 *lastKeyboard;
    int modifiers;
    int buttons;
    Point mouse;
    std::vector<SDL_Joystick*> joysticks;
    std::string text;

    static Input input;

    Input();
    ~Input();

protected:
    friend class Game;

    static void start();
    static void update();
    static void quit();

    void joyAdded(int joyID);
    void joyRemoved(int joyID);

    static bool checkKeyboard(int key);
    static bool checkJoystick(int joyID);

public:
    static int getNumKeys();
    static int getNumJoysticks();
    static int getNumAxes(int joyID);
    static int getNumBalls(int joyID);
    static int getNumButtons(int joyID);
    static int getNumHats(int joyID);

    static const char*  getKeyName(int key);
    static int          getKeyFromName(const char* name);
    static const char*  getJoystickName(int joyID);

    static bool         getKey(int key);
    static bool         getKeyDown(int key);
    static bool         getKeyUp(int key);
    static bool         getModifiers(int modifiers); // keyboard modifiers OR'd
    static bool         getButtons(int buttons);     // mouse buttons OR'd
    static const Point &getMouse();
    static bool         getJoystickButton(int joyID, int button);
    static Sint16       getJoystickAxis(int joyID, int axis);
    static Uint8        getJoystickHat(int joyID, int hat);

    static const std::string   &getText();
    static bool                 textEntered();
};

}
