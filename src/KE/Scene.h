#pragma once
#include <list>
#include <queue>

#include "Object.h"

namespace KE
{

class Scene
{
    class ObjectSorter
    {
    public:
        bool operator() (const Object *a, const Object *b) const
        {
            return a->getZ() > b->getZ();
        }
    };

    using ObjectList = std::list<Object*>;
    using ObjectQueue = std::priority_queue<Object*, std::vector<Object*>, ObjectSorter>;

    ObjectList objects;

    void unload();

protected:
    friend class Game;

    Scene();
    ~Scene();

    void makeDrawQueue(ObjectQueue &oq);
    void transferTo(Scene &s);
    void receive(ObjectList &ol);

    Object *findObject(const std::string &keyname) const;

public:
    void start();
    void exit();
    void rearrange();
};

}
