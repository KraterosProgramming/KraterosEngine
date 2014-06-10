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
    for (auto &i : adding)
    {
        if (i)
        {
            i.destroyObject();
        }
    }
    adding.clear();

    for (auto &i : instances)
    {
        if (i)
        {
            i.destroyObject();
        }
    }
    instances.clear();
}

void Scene::transferTo(Scene &s)
{
    s.receive(instances);
}

void Scene::receive(List &il)
{
    instances.splice(instances.end(), il);
}

const Instance<Object> &Scene::add(Object* object)
{
    adding.push_back(Instance<Object>());
    adding.back().create(object);
    return adding.back();
}

const Instance<Object> Scene::findInstance(const std::string &keyname) const
{
    for (auto &i : instances)
    {
        if (i->getKeyname() == keyname)
        {
            return i;
        }
    }

    return Instance<Object>();
}

void Scene::start()
{
    onStart();
}

void Scene::close()
{
    onClose();
    for (auto &i : instances)
    {
        i->close();
    }
}

void Scene::arrange()
{
    onArrange();
    for (auto &i : instances)
    {
        if (i)
        {
            i->arrange();
        }
    }
}

void Scene::think()
{
    onThink();
    for (auto &i : instances)
    {
        if (i)
        {
            i->think();
        }
    }
}

void Scene::update()
{
    for (auto &i : adding)
    {
        if (i)
        {
            i->start();
            i->arrange();
        }
    }

    instances.splice(instances.end(), adding);

    onUpdate();
    for (auto &i : instances)
    {
        if (i)
        {
            i->update();
        }
    }

    auto it = instances.begin();
    while (it != instances.end())
    {
        if (!(*it))
        {
            it = instances.erase(it);
        }
        else if (!(*it)->isAlive())
        {
            (*it)->death();
            (*it).destroyObject();
            it = instances.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Scene::draw()
{
    onDraw();
    for (auto &i : instances)
    {
        if (i)
        {
            i->draw();
        }
    }
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
