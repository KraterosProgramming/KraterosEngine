#pragma once
#ifdef KRATEROS_ENGINE_DEBUG
    #include <iostream>
#else
    #include <fstream>
#endif // KRATEROS_ENGINE_DEBUG

namespace KE
{

class Console
{
protected:
#ifdef KRATEROS_ENGINE_RELEASE
    static std::ofstream logFile;
    static std::ofstream warningFile;
    static std::ofstream errorFile;
#else
    static std::ostream &logFile;
    static std::ostream &warningFile;
    static std::ostream &errorFile;
#endif // KRATEROS_ENGINE_RELEASE
    std::ostream &file;

public:
    Console(std::ostream &file);
    virtual ~Console();

    template<typename T>
    Console &operator << (const T &t);
};

template<typename T>
Console &Console::operator << (const T &t)
{
    file << t;
    return *this;
}

class Log : public Console
{
public:
    static int numLogs;
    Log();
};

class Warning : public Console
{
public:
    static int numWarnings;
    Warning();
};

class Error : public Console
{
public:
    static int numErrors;
    Error();
};

}
