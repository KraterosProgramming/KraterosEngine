#include "Console.h"

namespace KE
{

#ifdef KRATEROS_ENGINE_RELEASE
std::ofstream Console::logFile("logs.txt");
std::ofstream Console::warningFile("logs.txt");
std::ofstream Console::errorFile("errors.txt");
#else
std::ostream &Console::logFile = std::cout;
std::ostream &Console::warningFile = std::cout;
std::ostream &Console::errorFile = std::cerr;
#endif // KRATEROS_ENGINE_RELEASE

Console::Console(std::ostream &file) : file(file)
{

}

Console::~Console()
{
    file << std::endl;
}

int Log::numLogs = 0;
int Warning::numWarnings = 0;
int Error::numErrors = 0;

Log::Log() : Console(logFile)
{
    ++numLogs;
    file << "log: ";
}

Warning::Warning() : Console(warningFile)
{
    ++numWarnings;
    file << "WARNING! ";
}

Error::Error() : Console(errorFile)
{
    ++numErrors;
    file << "ERROR!! ";
}

}
