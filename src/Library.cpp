#include "Library.h"

namespace KE
{

Library Library::library;

Library::Library() :
    textures({"jpg", "png"}),
    sprites({"sprite"}),
    cursors({"cursor"}),
    musics({"ogg"}),
    sounds({"ogg"}),
    fonts({"font"})
{

}

bool Library::loadTextures(const std::string &directory)
{
    return library.textures.loadDirectory(directory);
}

bool Library::loadSprites(const std::string &directory)
{
    return library.sprites.loadDirectory(directory);
}

bool Library::loadCursors(const std::string &directory)
{
    return library.cursors.loadDirectory(directory);
}

bool Library::loadMusics(const std::string &directory)
{
    return library.musics.loadDirectory(directory);
}

bool Library::loadSounds(const std::string &directory)
{
    return library.sounds.loadDirectory(directory);
}

bool Library::loadFonts(const std::string &directory)
{
    return library.fonts.loadDirectory(directory);
}

Texture *Library::getTexture(const std::string &keyname)
{
    return library.textures.get(keyname);
}

Sprite *Library::getSprite(const std::string &keyname)
{
    return library.sprites.get(keyname);
}

Cursor *Library::getCursor(const std::string &keyname)
{
    return library.cursors.get(keyname);
}

Music *Library::getMusic(const std::string &keyname)
{
    return library.musics.get(keyname);
}

Sound *Library::getSound(const std::string &keyname)
{
    return library.sounds.get(keyname);
}

Font *Library::getFont(const std::string &keyname)
{
    return library.fonts.get(keyname);
}

}
