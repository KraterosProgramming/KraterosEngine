#include "Tools.h"
#include "tinydir.h"

namespace KE
{

size_t getFilesInDirectory(std::string directory, std::vector<std::string> &files, const std::vector<std::string> &extensions)
{
    if (directory.back() != '/')
    {
        directory += '/';
    }

    tinydir_dir dir;
    if (tinydir_open(&dir, directory.c_str()) < 0)
    {
        Error() << "could not open directory \"" << directory << "\"";
    }
    else
    {
        tinydir_file file;
        std::string path;

        while (dir.has_next)
        {
            if (tinydir_readfile(&dir, &file) < 0)
            {
                Error() << "reading file at directory \"" << directory << "\"";
            }
            else
            {
                if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
                {
                    path = directory + file.name;

                    if (file.is_dir)
                    {
                        getFilesInDirectory(path, files, extensions);
                    }
                    else
                    {
                        std::string ext = path.substr(path.find_last_of('.') + 1);
                        if (std::find(extensions.begin(), extensions.end(), ext) != extensions.end())
                        {
                            files.push_back(path);
                        }
                    }
                }
            }

            tinydir_next(&dir);
        }

        tinydir_close(&dir);
    }

    return files.size();
}

}
