
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

constexpr wchar_t      COLON          = ':';
constexpr wchar_t      SEMICOLON      = ';';
constexpr wchar_t      ASSIGNMENT     = '=';
constexpr wchar_t      SPACE          = ' ';
constexpr wchar_t      ENTER          = '\n';
constexpr std::wstring END            = L"NUL";
constexpr std::pair    STRING_LITERAL = {L'\"', L'\''};
const std::wstring     NUMBER         = L"число";
const std::wstring     STRING         = L"строка";
const std::wstring     CHARACTER      = L"символ";


[[nodiscard]] std::wstring test_func_convert(wchar_t ch);

const std::vector<std::pair<TokenType, std::wstring>> TYPE_CHAR_
{
        {TokenType::COLON, test_func_convert(COLON)},
        {TokenType::SEMICOLON, test_func_convert(SEMICOLON)},
        {TokenType::ASSIGNMENT, test_func_convert(ASSIGNMENT)},
};

// const std::vector<std::pair<TokenType, wchar_t>> TYPE_CHAR_
// {
//         {TokenType::COLON, COLON},
//         {TokenType::SEMICOLON, SEMICOLON},
//         {TokenType::ASSIGNMENT, ASSIGNMENT},
// };

const std::vector<std::pair<TokenType, std::wstring>> TYPE_DATA_
{
        {TokenType::NUMBER_DATATYPE, NUMBER},
        {TokenType::STRING_DATATYPE, STRING},
        {TokenType::CHARACTER_DATATYPE, CHARACTER},
};



[[nodiscard]] bool IsDigit(wchar_t number);
[[nodiscard]] bool IsSpace(wchar_t _ch);
[[nodiscard]] bool IsSymbol(wchar_t _ch);
[[nodiscard]] bool IsLetterOrDigit(wchar_t _ch);
[[nodiscard]] bool is_func(wchar_t ch);
[[nodiscard]] bool isEnter(wchar_t ch);
[[nodiscard]] bool isQuote(wchar_t ch);
[[nodiscard]] bool is_func_E_Q_S(wchar_t ch);

[[nodiscard]] std::wstring ConvertString(const std::string& string);


#endif //CONFIG_HPP
