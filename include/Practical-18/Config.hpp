
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <functional>
#include <memory>
#include <vector>

#include "TokenType.hpp"

#define TEST false
#define DEBUG false

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

const std::wstring     NUMBER_LITERAL = L"1234567890";
const std::wstring     ALPHOVIT       = L"йцукенгшщзхъфывапролджэячсмитьбю";

const std::vector<std::pair<TokenType, wchar_t>> TYPE_CHAR_
{
    {TokenType::COLON, COLON},
    {TokenType::SEMICOLON, SEMICOLON},
    {TokenType::ASSIGNMENT, ASSIGNMENT},
};

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
[[nodiscard]] bool test_func_bool(wchar_t ch, wchar_t i, bool is);

[[nodiscard]] std::wstring ConvertString(const std::string& string);

[[nodiscard]] std::wstring test_st(const std::wstring& _input, int& position,
    const std::function<bool(wchar_t)>& func);

[[nodiscard]] std::function<bool(const wchar_t&)> test_bind(wchar_t ch, bool is);

template<typename T>
[[nodiscard]] std::wstring test_func_wstring(const T& t)
{
    std::wstring io;
    io = t;
    return io;
}

#endif //CONFIG_HPP
