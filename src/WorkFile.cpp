
#include "WorkFile.hpp"


#include <fstream>
#include <iostream>


void CheackCanOpenFile(const bool te)
{
    if (!te)
    {
        std::cout << "File not open!!!" << std::endl;
        exit(EXIT_FAILURE);
    }
}


// [[nodiscard]] std::wstring ReadFile(const std::string& name)
// {
//     std::ifstream file(name);
//     CheackCanOpenFile(file.is_open());
//
//     std::string text;
//     std::string s;
//     while(getline(file, s))
//         text += s;
//
//     file.close();
//     return ConvertString(text);
// }
