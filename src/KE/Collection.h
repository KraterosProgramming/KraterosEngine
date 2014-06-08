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
    ~Collection();

    bool loadFromFile(const std::string &path, const std::string &keyname);
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
Collection<T>::~Collection()
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
bool Collection<T>::loadFromFile(const std::string &path, const std::string &keyname)
{
    T* loaded = new T();
    if (!loaded->loadFromFile(path))
    {
        delete loaded;
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
        Warning() << "could not find any proper file for " << name << " in directory " << directory;
    }
    else
    {
        for (auto &each : files)
        {
            std::string keyname = each.substr(0, each.find_last_of('.')); // TODO: Path class?
            if (!loadFromFile(each, keyname))
            {
                ok = false;
            }
        }
    }
    return ok;
}

template<class T>
T *Collection<T>::get(const std::string &keyname)
{
    T* found = nullptr;
    if (!collection.count(keyname))
    {
        Error() << "element with keyname \"" << keyname << "\" not loaded";
    }
    else
    {
        found = collection[keyname];
    }
    return found;
}

}
