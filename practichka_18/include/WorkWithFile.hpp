#ifndef WORKWITHFILE_HPP
#define WORKWITHFILE_HPP

#include <iostream>
#include <string>
#include <fstream>

[[nodiscard]] std::wstring ReadFile(const std::string& filename);

template<typename T>
void WriteFile(const std::string& filename, const T& data)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "NOT OPEN FILE!!!";
        exit(EXIT_FAILURE);
    }

    file << data;
    file.close();
}

#endif