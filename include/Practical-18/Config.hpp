
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

enum class Tokes
{
        NUMBER_DATATYPE,
        STRING_DATATYPE,

        COLON,          // двоеточие
        SEMICOLON,      // точка с запятой
        ASSIGNMENT,     // присваиваивание

        NUMBER,
        STRING,
        CHARACTER,
        ID,

        END,
};

inline const std::wstring& getWchar()
{
        return L":;=";
}

constexpr std::vector<std::wstring> typ {L"число", L"строка", L"символ"};


[[nodiscard]] std::wstring ConvertString(const std::string& string);


#endif //CONFIG_HPP
