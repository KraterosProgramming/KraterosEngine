#pragma once

#include "Pointer.h"

namespace KE
{

template<class T>
class Instance
{
    Pointer *pointer;

public:
    Instance();
    ~Instance();

    void create(Object *object);
    void destroyObject();

    void setPointer(Pointer *pointer);
    Pointer *getPointer() const;
    T *getObject() const;

    operator T* ()  const;
    T *operator-> () const;

    template<class U> Instance<T> &operator= (const Instance<U> &other);
};

template<class T> Instance<T>::Instance()
{
    this->pointer = nullptr;
}

template<class T> Instance<T>::~Instance()
{
    if (pointer)
    {
        pointer->dec();
        if (!pointer->getCount())
        {
            delete pointer;
        }
    }
}

template<class T> void Instance<T>::create(Object *object)
{
    setPointer(new Pointer(object));
}

template<class T> void Instance<T>::destroyObject()
{
    if (!pointer)
    {
         Error() << "trying to destroy null pointer";
    }
    else
    {
        pointer->destroy();
    }
}

template<class T> void Instance<T>::setPointer(Pointer *pointer)
{
    if (this->pointer)
    {
        this->pointer->dec();
        if (!this->pointer->getCount())
        {
            delete this->pointer;
        }
    }

    this->pointer = pointer;
    this->pointer->inc();
}

template<class T> Pointer *Instance<T>::getPointer() const
{
    return this->pointer;
}

template<class T> T *Instance<T>::getObject() const
{
    if (!pointer)
    {
        return nullptr;
    }
    else
    {
        return (T*)(pointer->getObject());
    }
}

template<class T> Instance<T>::operator T* () const
{
    return getObject();
}

template<class T> T *Instance<T>::operator-> () const
{
    return getObject();
}

template<class T> template<class U> Instance<T> &Instance<T>::operator= (const Instance<U> &other)
{
    setPointer(other.getPointer);
    return *this;
}

}
