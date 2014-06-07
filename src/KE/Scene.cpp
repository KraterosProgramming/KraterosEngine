#include "Scene.h"

namespace KE
{

Scene::Scene()
{

}

Scene::~Scene()
{
    unload();
}

void Scene::unload()
{
    for (auto &o : objects)
    {
        if (o)
        {
            delete o;
        }
    }
    objects.clear();
}

void Scene::makeDrawQueue(ObjectQueue &oq)
{

}

void Scene::transferTo(Scene &s)
{
    s.receive(objects);
}

void Scene::receive(ObjectList &ol)
{
    objects.splice(objects.end(), ol);
}

Object *Scene::findObject(const std::string &keyname) const
{
    Object *found = nullptr;
    for (auto it = objects.begin(); it != objects.end() && !found; ++it)
    {
        if ((*it)->getKeyname() == keyname)
        {
            found = *it;
        }
    }
    return found;
}

}
