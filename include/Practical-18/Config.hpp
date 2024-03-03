
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

        NUMBER_DATATYPE,
        STRING_DATATYPE,
        CHARACTER_DATATYPE,
        ID,

        END,
};

constexpr std::pair<wchar_t, wchar_t> STRING_LITERAL = {'\"', '\''};

constexpr wchar_t      COLON      = ':';
constexpr wchar_t      SEMICOLON  = ';';
constexpr wchar_t      ASSIGNMENT = '=';
constexpr wchar_t      SPACE      = ' ';
constexpr std::wstring END        = L"NUL";
constexpr std::wstring _NUMBER     = L"число";
constexpr std::wstring _STRING     = L"строка";
constexpr std::wstring _CHARACTER  = L"символ";

[[nodiscard]] bool IsDigit(wchar_t number);
[[nodiscard]] bool IsSpace(wchar_t _ch);
[[nodiscard]] bool IsSymbol(wchar_t _ch);
[[nodiscard]] bool IsLetterOrDigit(wchar_t _ch);

[[nodiscard]] std::wstring ConvertString(const std::string& string);


#endif //CONFIG_HPP
