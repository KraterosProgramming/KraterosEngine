#include "Input.h"
#include "Tools.h"
#include "Game.h"

namespace KE
{

Input Input::input;
const size_t Input::maxJoysticks = 4;

Input::Input() : joysticks(maxJoysticks, nullptr)
{
    this->numKeys = 0;
    this->keyboard = nullptr;
    this->lastKeyboard = nullptr;
    this->modifiers = KMOD_NONE;
    this->buttons = 0;
    this->lastButtons = 0;
}

Input::~Input()
{
    if (lastKeyboard)
    {
        delete[] lastKeyboard;
        lastKeyboard = nullptr;
    }
}

void Input::start()
{
    input.keyboard = SDL_GetKeyboardState(&input.numKeys);
    input.lastKeyboard = new Uint8[input.numKeys];
}

void Input::update()
{
    for (int i = 0; i < input.numKeys; ++i)
    {
        input.lastKeyboard[i] = input.keyboard[i];
    }
    input.lastButtons = input.buttons;
    input.text = "";

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                Game::exit();
            }
            break;

            case SDL_JOYDEVICEADDED:
            {
                input.joyAdded(event.jdevice.which);
            }
            break;

            case SDL_JOYDEVICEREMOVED:
            {
                input.joyRemoved(event.jdevice.which);
            }
            break;

            case SDL_TEXTINPUT:
            {
                input.text = event.text.text;
            }
            break;
        }
    }

    input.modifiers = SDL_GetModState();
    input.buttons = SDL_GetMouseState(&input.mouse.x, &input.mouse.y);
}

void Input::quit()
{
    for (size_t i = 0; i < maxJoysticks; ++i)
    {
        if (input.joysticks[i])
        {
            SDL_JoystickClose(input.joysticks[i]);
        }
    }

    Log() << "input closed";
}

void Input::joyAdded(int sdlJoyID)
{
    int joyID = sdlJoyID - 1;
    if (joysticks[joyID])
    {
        Warning() << "joystick " << sdlJoyID << " already added; reloading";
        SDL_JoystickClose(joysticks[joyID]);
        joysticks[joyID] = nullptr;
    }

    SDL_Joystick *added = SDL_JoystickOpen(sdlJoyID);
    if (!added)
    {
        Error() << "could not add joystick:" << SDL_GetError();
    }
    else
    {
        joysticks[joyID] = added;
    }
}

void Input::joyRemoved(int sdlJoyID)
{
    int joyID = sdlJoyID - 1;
    if (!joysticks[joyID])
    {
        Warning() << "joystick " << sdlJoyID << " has not been loaded";
    }
    else
    {
        SDL_JoystickClose(joysticks[joyID]);
        joysticks[joyID] = nullptr;
    }
}

bool Input::checkKeyboard(int key)
{
    if (!input.keyboard)
    {
        Warning() << "keyboard not started";
    }
    else if (key >= input.numKeys)
    {
        Warning() << "key " << getKeyName(key) << " not supported";
    }
    else
    {
        return true;
    }
    return false;
}

bool Input::checkJoystick(int joyID)
{
    if (!input.joysticks[joyID])
    {
        Warning() << "joystick " << joyID+1 << " not loaded";
    }
    else
    {
        return true;
    }
    return false;
}

int Input::getNumKeys()
{
    return input.numKeys;
}

int Input::getNumJoysticks()
{
    int count = 0;
    for (size_t i = 0; i < maxJoysticks; ++i)
    {
        if (input.joysticks[i])
        {
            ++count;
        }
    }
    return count;
}

int Input::getNumAxes(int joyID)
{
    checkJoystick(joyID);
    return SDL_JoystickNumAxes(input.joysticks[joyID]);
}

int Input::getNumBalls(int joyID)
{
    checkJoystick(joyID);
    return SDL_JoystickNumBalls(input.joysticks[joyID]);
}

int Input::getNumButtons(int joyID)
{
    checkJoystick(joyID);
    return SDL_JoystickNumButtons(input.joysticks[joyID]);
}

int Input::getNumHats(int joyID)
{
    checkJoystick(joyID);
    return SDL_JoystickNumHats(input.joysticks[joyID]);
}

bool Input::getKey(int key)
{
    if (checkKeyboard(key))
    {
        return input.keyboard[key];
    }
    return false;
}

bool Input::getKeyDown(int key)
{
    if (input.checkKeyboard(key))
    {
        return input.keyboard[key] && !input.lastKeyboard[key];
    }
    return false;
}

bool Input::getKeyUp(int key)
{
    if (input.checkKeyboard(key))
    {
        return input.lastKeyboard[key] && !input.keyboard[key];
    }
    return false;
}

bool Input::getModifier(int modifiers)
{
    return (input.modifiers & modifiers) == modifiers;
}

bool Input::getButton(int buttons)
{
    return (input.buttons & buttons) == buttons;
}

bool Input::getButtonDown(int button)
{
    return (input.buttons & button) == button && (input.lastButtons & button) != button;
}

bool Input::getButtonUp(int button)
{
    return (input.lastButtons & button) == button && (input.buttons & button) != button;
}

const Point &Input::getMouse()
{
    return input.mouse;
}

bool Input::getJoystickButton(int joyID, int button)
{
    checkJoystick(joyID);
    return SDL_JoystickGetButton(input.joysticks[joyID], button);
}

Sint16 Input::getJoystickAxis(int joyID, int axis)
{
    checkJoystick(joyID);
    return SDL_JoystickGetAxis(input.joysticks[joyID], axis);
}

Uint8 Input::getJoystickHat(int joyID, int hat)
{
    checkJoystick(joyID);
    return SDL_JoystickGetHat(input.joysticks[joyID], hat);
}

const char* Input::getKeyName(int key)
{
    return SDL_GetScancodeName((SDL_Scancode)key);
}

int Input::getKeyFromName(const char* name)
{
    return SDL_GetScancodeFromName(name);
}

const char* Input::getJoystickName(int joyID)
{
    checkJoystick(joyID);
    return SDL_JoystickName(input.joysticks[joyID]);
}

const std::string &Input::getText()
{
    return input.text;
}

bool Input::textEntered()
{
    return input.text.size();
}

}
