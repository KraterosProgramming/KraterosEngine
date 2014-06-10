#include "Library.h"

namespace KE
{

Library Library::library;

Library::Library() :
    textures("Textures", {"jpg", "png"}),
    tilesets("Tilesets", {"tileset"}),
    cursors("Cursors", {"cursor"}),
    musics("Musics", {"ogg"}),
    sounds("Sounds", {"ogg"}),
    fonts("Fonts", {"font"})
{

}

void Library::quit()
{
    library.textures.quit();
    library.tilesets.quit();
    library.cursors.quit();
    library.musics.quit();
    library.sounds.quit();
    library.fonts.quit();

    Log() << "library closed";
}

bool Library::loadTextures(const std::string &directory)
{
    return library.textures.loadDirectory(directory);
}

bool Library::loadTilesets(const std::string &directory)
{
    return library.tilesets.loadDirectory(directory);
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

Tileset *Library::getTileset(const std::string &keyname)
{
    return library.tilesets.get(keyname);
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
