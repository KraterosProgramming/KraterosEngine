#pragma once
#include <list>
#include <queue>

#include "Object.h"

namespace KE
{

class Scene
{
    template<bool frontFirst>
    class ObjectSorter
    {
    public:
        bool operator() (const Object *a, const Object *b) const
        {
            return a->getZ() > b->getZ();
        }
    };

    using ObjectList = std::list<Object*>;

    ObjectList objects;

    void unload();

protected:
    friend class Game;

    Scene();
    virtual ~Scene();

    void transferTo(Scene &s);
    void receive(ObjectList &ol);

    void add(Object* o);
    Object *findObject(const std::string &keyname) const;

public:
    void start();
    void close();
    void arrange();

    virtual void onStart() { }
    virtual void onClose() { }
    virtual void onArrange() { }
};

}
