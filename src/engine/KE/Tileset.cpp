#include "Tileset.h"
#include "Geometry.h"
#include "Tools.h"
#include "Library.h"

namespace KE
{

Tileset::Tileset()
{
    this->texture = nullptr;
}

Tileset::~Tileset()
{

}

bool Tileset::loadFromFile(const std::string &path)
{
    XMLDocument doc;
    XMLError loaded = doc.LoadFile(path.c_str());
    if (!loaded)
    {
        Error() << "opening XML file \"" << path << "\": XML error = " << loaded;
    }
    else
    {
        const XMLElement *spr = doc.FirstChildElement("sprite");
        if (!spr)
        {
            Error() << "no sprite element in file \"" << path << "\"";
        }
        else
        {
            const XMLElement *tex = spr->FirstChildElement("texture");
            if (!tex)
            {
                Error() << "no texture in sprite element of file \"" << path << "\"";
            }
            else
            {
                const char *texName = tex->Attribute("name");
                if (!texName)
                {
                    Error() << "no name attribute in texture element, file \"" << path << "\"";
                }
                else
                {
                    texture = Library::getTexture(texName);
                    if (!texture)
                    {
                        Error() << "texture " << texName << " not loaded";
                    }
                    else
                    {
                        const XMLElement *frms = spr->FirstChildElement("frames");
                        if (!frms)
                        {
                            frames.push_back(texture->getClip());
                        }
                        else
                        {
                            for (const XMLElement *frm = frms->FirstChildElement("frame"); frm != nullptr; frm = frm->NextSiblingElement("frame"))
                            {
                                frames.push_back(Rect(frm->IntAttribute("x"), frm->IntAttribute("y"), frm->IntAttribute("w"), frm->IntAttribute("h")));
                            }
                        }

                        const XMLElement *anms = spr->FirstChildElement("animations");
                        std::vector<size_t> frameIDs;
                        if (!anms)
                        {
                            frameIDs.push_back(0);
                            animations.insert( std::pair<std::string, Animation>("idle", Animation(1, frameIDs)) );
                        }
                        else
                        {
                            for (const XMLElement *anm = anms->FirstChildElement("animation"); anm != nullptr; anm = anm->NextSiblingElement("animation"))
                            {
                                frameIDs.clear();
                                for (const XMLElement *frm = anms->FirstChildElement("frame"); frm != nullptr; frm = frm->NextSiblingElement("frame"))
                                {
                                    frameIDs.push_back(frm->IntAttribute("id"));
                                }
                                animations.insert(std::pair<std::string, Animation>(anm->Attribute("name"), Animation(anm->IntAttribute("fps"), frameIDs)));
                            }
                        }

                        return true;
                    }
                }
            }
        }
    }
    return false;
}

const Animation *Tileset::getAnimation(const std::string &keyname) const
{
    std::map<std::string, Animation>::const_iterator found = animations.find(keyname);
    if (found == animations.end())
    {
        Error() << "cant find animation \"" << keyname << "\"";
    }
    else
    {
        return &found->second;
    }
    return nullptr;
}

void Tileset::draw(const Point &position, size_t frame) const
{
    if (!texture)
    {
        Error() << "no texture associated to this tileset.";
    }
    else if (frame >= frames.size())
    {
        Error() << "trying to render frame number " << frame << " from " << frames.size() << " frames.";
    }
    else
    {
        texture->draw(position, frames[frame]);
    }
}

void Tileset::draw(const Point &position, const Rect &bounds, size_t frame) const
{
    if (!texture)
    {
        Error() << "no texture associated to this tileset.";
    }
    else if (frame >= frames.size())
    {
        Error() << "trying to render frame number " << frame << " from " << frames.size() << " frames.";
    }
    else
    {
        Point final_position (std::max(position.x, bounds.x), std::max(position.y, bounds.y));
        Rect final_source = Geometry::intersect(frames[frame], bounds.move(-position));
        texture->draw(final_position, final_source);
    }
}

}
