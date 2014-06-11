#pragma once
#include <map>
#include <string>
#include "Tools.h"

namespace KE
{

template<class T>
class Collection
{
    std::string name;
    std::map<std::string, T*> collection;
    std::vector<std::string> extensions;

public:
    Collection(const std::string &name, std::initializer_list<std::string> extensions);

    void quit();

    bool load(const std::string &path, const std::string &keyname);
    bool loadDirectory(const std::string &directory);
    T *get(const std::string &keyname);
};

template<class T>
Collection<T>::Collection(const std::string &name, std::initializer_list<std::string> extensions)
{
    this->name = name;
    this->extensions = extensions;
}

template<class T>
void Collection<T>::quit()
{
	for (auto &each : collection)
    {
        if (each.second)
        {
            delete each.second;
        }
    }
    collection.clear();
}

template<class T>
bool Collection<T>::load(const std::string &path, const std::string &keyname)
{
    T* loaded = new T();
    if (!loaded->loadFromFile(path))
    {
        delete loaded;
        loaded = nullptr;
    }
    else
    {
        collection[keyname] = loaded;
    }
    return loaded;
}

template<class T>
bool Collection<T>::loadDirectory(const std::string &directory)
{
    bool ok = true;
    std::vector<std::string> files;
    if (!getFilesInDirectory(directory, files, extensions))
    {
        Warning() << "could not find any " << name << " file in directory " << directory;
    }
    else
    {
        for (auto &each : files)
        {
            std::string keyname = each.substr(0, each.find_last_of('.')).substr(directory.size());
            ok = ok && load(each, keyname);
        }
    }

    if (!ok)
    {
        Error() << "could not load " << name << " directory \"" << directory << "\"";
    }

    return ok;
}

template<class T>
T *Collection<T>::get(const std::string &keyname)
{
    T* found = nullptr;
    if (!collection.count(keyname))
    {
        Error() << name << " with keyname \"" << keyname << "\" not loaded";
    }
    else
    {
        found = collection[keyname];
    }
    return found;
}

}
