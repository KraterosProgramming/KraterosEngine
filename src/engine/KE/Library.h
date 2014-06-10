#pragma once
#include <map>
#include <string>

#include "Collection.h"
#include "Texture.h"
#include "Tileset.h"
#include "Cursor.h"
#include "Music.h"
#include "Sound.h"
#include "Font.h"

namespace KE
{

class Library
{
    Collection<Texture> textures;
    Collection<Tileset> tilesets;
    Collection<Cursor> cursors;
    Collection<Music> musics;
    Collection<Sound> sounds;
    Collection<Font> fonts;

    static Library library;

protected:
    friend class Game;

    Library();

    static void quit();

    static bool loadTextures(const std::string &directory);
    static bool loadTilesets(const std::string &directory);
    static bool loadCursors(const std::string &directory);
    static bool loadMusics(const std::string &directory);
    static bool loadSounds(const std::string &directory);
    static bool loadFonts(const std::string &directory);

public:
    static Texture *getTexture(const std::string &keyname);
    static Tileset *getTileset(const std::string &keyname);
    static Cursor *getCursor(const std::string &keyname);
    static Music *getMusic(const std::string &keyname);
    static Sound *getSound(const std::string &keyname);
    static Font *getFont(const std::string &keyname);
};

}
