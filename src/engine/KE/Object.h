#pragma once
#include <string>

#include "Geometry.h"


namespace KE
{

class Object
{
    std::string keyname;
    Uint32 tags;
    bool alive;
    Point position; // TODO: float position
    int z;

protected:
    void setKeyname(const std::string &keyname);
    void addTags(Uint32 tags);

    virtual void onStart() { }
    virtual void onClose() { }
    virtual void onDeath() { }
    virtual void onThink() { }
    virtual void onUpdate() { }
    virtual void onDraw() { }
    virtual void onArrange() { }

public:
    Object();
    Object(const Point &position, int z = 0);
    virtual ~Object();

    std::string getKeyname() const;
    bool hasTags(Uint32 tags) const;
    bool isAlive() const;
    void die();

    const Point getPosition() const;
    void setPosition(const Point &position);
    void move(const Point &movement);

    int getZ() const;
    void setZ(int z);

    void start();
    void close();
    void death();
    void think();
    void update();
    void draw();
    void arrange();
};

}
