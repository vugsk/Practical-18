
#include "../include/WorkWithFile.hpp"

#include "Config.hpp"


[[nodiscard]] std::wstring ReadFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        puts("ERROR: NOT OPEN FILE");
        exit(EXIT_FAILURE);
    }

    const long size = file.seekg(0, std::ios::end).tellg();
    file.seekg(0);

    std::string te;
    te.resize(size);
    file.read(&te[0], size);

    file.close();
    return ConvertString(te);
}
