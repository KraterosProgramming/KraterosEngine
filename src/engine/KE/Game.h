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
    int audioFrequency;
    int audioChunkSize;
    int audioChannels;

    const char *texturesDir;
    const char *tilesetsDir;
    const char *cursorsDir;
    const char *musicsDir;
    const char *soundsDir;
    const char *fontsDir;

    Game(const Point &startingSize, const std::string &title);
    virtual ~Game();

public:
    static const int subsystems;
    static const int imageTypesSupport;
    static const int audioTypesSupport;
    static const int audioFormat;

    static const int defaultAudioFrequency;
    static const int defaultAudioChunkSize;
    static const int defaultAudioChannels;

    static const char *defaultTexturesDir;
    static const char *defaultTilesetsDir;
    static const char *defaultCursorsDir;
    static const char *defaultMusicsDir;
    static const char *defaultSoundsDir;
    static const char *defaultFontsDir;

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
