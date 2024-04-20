#ifndef WORKWITHFILE_HPP
#define WORKWITHFILE_HPP

#include <iostream>
#include <string>
#include <fstream>

[[nodiscard]] std::wstring read_file_test(const std::string& filename);

template<typename T>
void Write_file(const std::string& filename, const T& data)
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