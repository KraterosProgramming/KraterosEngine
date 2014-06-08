#pragma once
#include <map>
#include <string>

#include "Collection.h"
#include "Texture.h"
#include "Sprite.h"
#include "Cursor.h"
#include "Music.h"
#include "Sound.h"
#include "Font.h"

namespace KE
{

class Library
{
    Collection<Texture> textures;
    Collection<Sprite> sprites;
    Collection<Cursor> cursors;
    Collection<Music> musics;
    Collection<Sound> sounds;
    Collection<Font> fonts;

    static Library library;

protected:
    friend class Game;

    Library();
    ~Library();

    static bool loadTextures(const std::string &directory);
    static bool loadSprites(const std::string &directory);
    static bool loadCursors(const std::string &directory);
    static bool loadMusics(const std::string &directory);
    static bool loadSounds(const std::string &directory);
    static bool loadFonts(const std::string &directory);

public:
    static Texture *getTexture(const std::string &keyname);
    static Sprite *getSprite(const std::string &keyname);
    static Cursor *getCursor(const std::string &keyname);
    static Music *getMusic(const std::string &keyname);
    static Sound *getSound(const std::string &keyname);
    static Font *getFont(const std::string &keyname);
};

}
