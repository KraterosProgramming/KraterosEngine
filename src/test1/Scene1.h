#pragma once
#include <KE/KE.h>
using namespace KE;

#include "Object1.h"

class Scene1 : public KE::Scene {
    virtual void onStart() override {
        Log() << "scene1 on start";
        add(new Object1());
    }
    virtual void onClose() override {
        Log() << "scene1 on close";
    }
    virtual void onArrange() override {
        Log() << "scene1 on arrange";
    }
    virtual void onThink() override {
        Log() << "scene1 on think";
    }
    virtual void onUpdate() override {
        Log() << "scene1 on update";
    }
    virtual void onDraw() override {
        Log() << "scene1 on draw";
    }
public:
    Scene1() {
        Log() << "new scene1";
    }
    ~Scene1() {
        Log() << "delete scene1";
    }
};
