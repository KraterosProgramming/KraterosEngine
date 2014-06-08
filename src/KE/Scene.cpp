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

void Scene::transferTo(Scene &s)
{
    s.receive(objects);
}

void Scene::receive(ObjectList &ol)
{
    objects.splice(objects.end(), ol);
}

void Scene::add(Object* o)
{
    objects.push_back(o);
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

void Scene::start()
{
    onStart();
}

void Scene::close()
{
    onClose();
}

void Scene::arrange()
{
    onArrange();
}

template<>
bool Scene::ObjectSorter<false>::operator() (const Object *a, const Object *b) const
{
    return a->getZ() > b->getZ();
}

template<>
bool Scene::ObjectSorter<true>::operator() (const Object *a, const Object *b) const
{
    return a->getZ() < b->getZ();
}

}
