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
    Point startingSize;
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
    Game(const Point &startingSize, const std::string &title);
    Game(const Point &startingSize, const std::string &title, int audioFrequency, int audioChunkSize);
    virtual ~Game();

public:
    static const int defaultAudioFrequency;
    static const int defaultAudioChunkSize;

    static int getResult();

    static const Point getWindowSize();
    static void setWindowSize(const Point &size);

    static Renderer &getRenderer();

    void start();
    static void exit();
    static void exit(int errorCode);

    virtual int onStart() = 0;  // return error code, or 0 if OK
    virtual bool onExit() = 0;  // return false for cancel exit

    static void add(Object* o);
    static Object *findObject(const std::string &keyname);

    static void startScene(Scene *scene);
    static void combineScene(Scene *scene);
};

}
