
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>

enum class TokenType
{
        COLON,          // двоеточие
        SEMICOLON,      // точка с запятой
        ASSIGNMENT,     // присваиваивание

        STRING_LITERAL, // кавычки
        NUMBER_LITERAL,

        NUMBER,
        STRING,
        CHARACTER,
        ID,

        END,
};

constexpr wchar_t COLON = ':';
constexpr wchar_t SEMICOLON = ';';
constexpr wchar_t ASSIGNMENT = '=';
constexpr wchar_t SPACE = ' ';

constexpr std::pair<wchar_t, wchar_t> STRING_LITERAL = {'\"', '\''};

constexpr std::vector<std::wstring> GetDataTypes()
{
        return {L"число", L"строка", L"символ"};
}


[[nodiscard]] std::wstring ConvertString(const std::string& string);


#endif //CONFIG_HPP
