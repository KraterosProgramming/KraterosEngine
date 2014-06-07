#pragma once
#include <iostream>

#define LOG_FILE        std::clog
#define WARNING_FILE    std::cerr
#define ERROR_FILE      std::cerr

namespace KE
{

class Console
{
protected:
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
