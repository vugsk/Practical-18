
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>

const enum class TokenType
{
        COLON,          // двоеточие
        SEMICOLON,      // точка с запятой
        ASSIGNMENT,     // присваиваивание

        NUMBER,
        STRING,
        CHARACTER,
        ID,

        END,
};

constexpr std::vector<wchar_t> CHAR_TYPE {':', ';', '='};

constexpr std::vector<std::wstring> DATA_TYPE {L"число", L"строка", L"символ"};


[[nodiscard]] std::wstring ConvertString(const std::string& string);


#endif //CONFIG_HPP
