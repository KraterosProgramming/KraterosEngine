#pragma once
#include <KE/KE.h>
using namespace KE;

class Object1 : public Object {
    virtual void onStart() {
        Log() << "object1 on start";
    }
    virtual void onClose() {
        Log() << "object1 on close";
    }
    virtual void onDeath() {
        Log() << "object1 on death";
    }
    virtual void onThink() {
        Log() << "object1 on think";
    }
    virtual void onUpdate() {
        Log() << "object1 on update";
    }
    virtual void onDraw() {
        Log() << "object1 on draw";
    }
    virtual void onArrange() {
        Log() << "object1 on arrange";
    }

public:
    Object1() {
        Log() << "new object1";
    }
    ~Object1() {
        Log() << "delete object1";
    }
};
