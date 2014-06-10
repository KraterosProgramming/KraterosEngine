#pragma once

#include "Scene.h"
#include "Window.h"
#include "Renderer.h"

namespace KE
{

class Game
{
    Point startingSize;
    std::string title;
    int audioFrequency, audioChunkSize;

    Window window;
    Renderer renderer;
    Scene *scene;       // TODO: support multiple scenes at background
    bool mustQuit;
    int result;
    Uint32 ticks;
    float deltaTime;

    static Game *game;

    bool init();
    void quit();
    void loop();

    virtual int onStart() { return 0; }  // return error code, or 0 if OK
    virtual bool onExit() { return true; };  // return false for cancel exit

protected:
    Game(const Point &startingSize, const std::string &title);
    Game(const Point &startingSize, const std::string &title, int audioFrequency, int audioChunkSize);
    virtual ~Game();

public:
    static const int subsystems;
    static const int imageTypesSupport;
    static const int audioTypesSupport;
    static const int audioFormat;
    static const int defaultAudioFrequency;
    static const int defaultAudioChunkSize;

    static int getResult();
    static Uint32 getTime();
    static float getDeltaTime();
    static const Point getWindowSize();
    static Window &getWindow();
    static Renderer &getRenderer();

    static void setWindowSize(const Point &size);

    void start();
    static void exit();
    static void exit(int errorCode);

    static void startScene(Scene *scene);
    static void combineScene(Scene *scene);
};

}
