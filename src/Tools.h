#pragma once
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "tinyxml2.h"

#include "Console.h"

namespace KE
{

size_t getFilesInDirectory(std::string directory, std::vector<std::string> &files, const std::vector<std::string> &extensions);

}
