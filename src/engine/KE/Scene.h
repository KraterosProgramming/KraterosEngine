#pragma once
#include <list>
#include <queue>

#include "Object.h"
#include "Tools.h"

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

    using List = std::list< Instance<Object> >;

    List instances, adding;

    void unload();

protected:
    friend class Game;

    Scene();
    virtual ~Scene();

    void transferTo(Scene &s);
    void receive(List &il);

    const Instance<Object> &add(Object *object);
    const Instance<Object> findInstance(const std::string &keyname) const;

    virtual void onStart() { }
    virtual void onClose() { }
    virtual void onArrange() { }
    virtual void onThink() { }
    virtual void onUpdate() { }
    virtual void onDraw() { }

public:
    void start();
    void close();
    void arrange();
    void think();
    void update();
    void draw();
};

}
