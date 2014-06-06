#pragma once
#include "Window.h"
#include "Renderer.h"

#define SUPPORTED_IMAGE_TYPES       (IMG_INIT_JPG|IMG_INIT_JPG)
#define SUPPORTED_AUDIO_TYPES       (MIX_INIT_OGG)
#define AUDIO_FREQUENCY             44100
#define AUDIO_CHUNK_SIZE            1024
#define WINDOW_WIDTH                800
#define WINDOW_HEIGHT               480
#define WINDOW_TITLE                "Krateros Engine"

namespace KE
{

class App
{
    Window window;
    Renderer renderer;

protected:
    friend class Game;

    App();
    ~App();

    bool init();
    void quit();
};

}
