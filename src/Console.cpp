#include "Console.h"

namespace KE
{

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

Log::Log() : Console(LOG_FILE)
{
    ++numLogs;
    file << "log: ";
}

Warning::Warning() : Console(WARNING_FILE)
{
    ++numWarnings;
    file << "warning! ";
}

Error::Error() : Console(ERROR_FILE)
{
    ++numErrors;
    file << "ERROR!! ";
}

}
