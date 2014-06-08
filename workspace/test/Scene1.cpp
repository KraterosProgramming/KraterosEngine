#include "Scene1.h"
#include "Object1.h"

Scene1::Scene1()
{
    KE::Warning() << "TO HARDCORE FOR THIS WORLD";
}

Scene1::~Scene1()
{
    KE::Log() << "such scene";
}

void Scene1::onStart()
{
    add(new Object1());
}
