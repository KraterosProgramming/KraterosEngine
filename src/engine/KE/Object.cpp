#include "Object.h"

namespace KE
{

Object::Object()
{
    this->keyname = "";
    this->tags = 0;

	this->alive = true;
	this->position = Point(0, 0);
	this->z = 0;
}

Object::Object(const Point &position, int z)
{
    this->keyname = "";
    this->tags = 0;

	this->alive = true;
	this->position = position;
	this->z = z;
}

Object::~Object()
{
    this->alive = false;
}

void Object::setKeyname(const std::string &keyname)
{
    this->keyname = keyname;
}

void Object::addTags(Uint32 tags)
{
    this->tags |= tags;
}

std::string Object::getKeyname() const
{
    return keyname;
}

bool Object::hasTags(Uint32 tags) const
{
    return (this->tags & tags) == tags;
}

bool Object::isAlive() const
{
    return alive;
}

void Object::die()
{
    alive = false;
}

const Point Object::getPosition() const
{
    return position;
}

void Object::setPosition(const Point &position)
{
    this->position = position;
}

void Object::move(const Point &movement)
{
    position += movement;
}

int Object::getZ() const
{
    return z;
}

void Object::setZ(int z)
{
    this->z = z;
}

void Object::start()
{
    onStart();
}

void Object::close()
{
    onClose();
}

void Object::death()
{
    onDeath();
}

void Object::think()
{
    onThink();
}

void Object::update()
{
    onUpdate();
}

void Object::draw()
{
    onDraw();
}

void Object::arrange()
{
    onArrange();
}

}
