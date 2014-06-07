#pragma once

#include "Scene.h"
#include "Window.h"
#include "Renderer.h"

#define INITIATED_SUBSYSTEMS        (SDL_INIT_EVERYTHING)
#define SUPPORTED_IMAGE_TYPES       (IMG_INIT_JPG|IMG_INIT_JPG)
#define SUPPORTED_AUDIO_TYPES       (MIX_INIT_OGG)
#define AUDIO_FORMAT                (MIX_DEFAULT_FORMAT)

namespace KE
{

class Game
{
    int w, h;
    std::string title;
    int audioFrequency, audioChunkSize;

    Window window;
    Renderer renderer;
    Scene *scene;       // TODO: support multiple scenes at background
    bool mustQuit;
    int result;

    static Game *game;

    bool init();
    void quit();
    void loop();

protected:
    Game(int w, int h, const std::string &title);
    Game(int w, int h, const std::string &title, int audioFrequency, int audioChunkSize);
    virtual ~Game();

public:
    static const int defaultAudioFrequency;
    static const int defaultAudioChunkSize;

    void start();
    static void exit();
    static void exit(int errorCode);

    virtual void onStart() = 0;
    virtual void onExit() = 0;

    static int getResult();
    static Window &getWindow();
    static Renderer &getRenderer();

    static Object *findObject(const std::string &keyname);

    static void startScene(Scene *scene);
    static void combineScene(Scene *scene);
};

}
