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
//    <tileset texture="textures/guy" />
//        <frames>  <!-- optional -->
//            <frame x="0" y="0" w="100" h="100" />
//            <frame x="100" y="0" w="100" h="100" />
//        </frame>
//        <animations>  <!-- optional -->
//            <animation name="walk" fps="24">
//                <frame id="0" />
//                <frame id="1" />
//            </animation>
//            <animation name="crouch" fps="24">
//                <frame id="0" />
//                <frame id="2" />
//            </animation>
//        </animations>
//    </tileset>

    bool ok = false;

    XMLDocument doc;
    XMLError error = doc.LoadFile(path.c_str());
    if (error != XML_NO_ERROR)
    {
        Error() << "opening tileset file \"" << path << "\": XML error = " << error;
    }
    else
    {
        const XMLElement *elem = doc.FirstChildElement("tileset");
        if (!elem)
        {
            Error() << "no tileset element in file \"" << path << "\"";
        }
        else
        {
            const char *textureKeyname = elem->Attribute("texture");
            if (!textureKeyname)
            {
                Error() << "no texture attribute in tileset element, in file \"" << path << "\"";
            }
            else
            {
                texture = Library::getTexture(textureKeyname);
                if (!texture)
                {
                    Error() << "invalid texture attribute in tileset element, in file \"" << path << "\"";
                }
                else
                {
                    float offsetX = elem->FloatAttribute("offsetX");
                    float offsetY = elem->FloatAttribute("offsetY");
                    // optional frames element
                    const XMLElement *framesElem = elem->FirstChildElement("frames");
                    if (!framesElem)
                    {
                        Rect source = texture->getClip();
                        Point offset(offsetX * source.w, offsetY * source.h);
                        frames.push_back({source, offset});
                    }
                    else
                    {
                        for (const XMLElement *f = framesElem->FirstChildElement("frame"); f != nullptr; f = f->NextSiblingElement("frame"))
                        {
                            Rect source = Rect::parseXML(f);

                            float frameOffsetX = offsetX;
                            float frameOffsetY = offsetY;
                            f->QueryFloatAttribute("offsetX", &offsetX);
                            f->QueryFloatAttribute("offsetY", &offsetY);
                            Point offset(frameOffsetX * source.w, frameOffsetY * source.h);
                            frames.push_back({source, offset});
                        }
                    }

                    // optional animations element
                    const XMLElement *animationsElem = elem->FirstChildElement("animations");
                    if (!animationsElem)
                    {
                        std::vector<size_t> firstFrame(1, 0);
                        animations.insert(std::pair<std::string, Animation>("idle", Animation(1, firstFrame)));
                    }
                    else
                    {
                        for (const XMLElement *a = animationsElem->FirstChildElement("animation"); a != nullptr; a = a->NextSiblingElement("animation"))
                        {
                            const char *name = a->Attribute("name");
                            if (!name)
                            {
                                name = "idle";
                            }

                            if (animations.count(name))
                            {
                                Error() << "duplicated animation name in file \"" << path << "\"";
                            }
                            else
                            {
                                int fps = a->IntAttribute("fps");
                                if (!fps)
                                {
                                    Error() << "no fps attribute (bigger than 0) in animation element, in file \"" << path << "\"";
                                }
                                else
                                {
                                    std::vector<size_t> frameIDs;
                                    for (const XMLElement *f = a->FirstChildElement("frame"); f != nullptr; f = f->NextSiblingElement("frame"))
                                    {
                                        frameIDs.push_back(f->UnsignedAttribute("id"));
                                    }

                                    if (!frameIDs.size())
                                    {
                                        Error() << "no frames subelements in element animation, in file \"" << path << "\"";
                                    }
                                    else
                                    {
                                        animations.insert(std::pair<std::string, Animation>(name, Animation(fps, frameIDs)));
                                    }
                                }
                            }
                        }
                    }

                    ok = true;
                }
            }
        }
    }

    return ok;
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
        Point final_position = position - frames[frame].source.getPosition() - frames[frame].offset;
        texture->draw(final_position, frames[frame].source);
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
        final_position -= frames[frame].source.getPosition();
        Rect final_source = Geometry::intersect(frames[frame].source, bounds.move(-position));
        texture->draw(final_position, final_source);
    }
}

}
