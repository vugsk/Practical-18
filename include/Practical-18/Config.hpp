
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <functional>
#include <memory>
#include <vector>

#include "Token.hpp"
#include "TokenType.hpp"

#define TEST false
#define DEBUG false


constexpr wchar_t      COLON             = ':';
constexpr wchar_t      SEMICOLON         = ';';
constexpr wchar_t      ASSIGNMENT        = '=';
constexpr wchar_t      SPACE             = ' ';
constexpr wchar_t      ENTER             = '\n';
constexpr wchar_t      STRING_LITERAL    = '\"';
constexpr wchar_t      CHARACTER_LITERAL = '\'';
constexpr std::wstring END               = L"NUL";
const std::wstring     NONE              = L"NONE";

const std::wstring     NUMBER         = L"число";
const std::wstring     STRING         = L"строка";
const std::wstring     CHARACTER      = L"символ";

constexpr std::pair NUMBER_LITERAL = {45, 57};
constexpr std::pair ALPHOVIT       = {1072, 1103};



const std::vector<std::pair<TokenType, wchar_t>> TYPE_CHAR_
{
    {colon, COLON},
    {semicolon, SEMICOLON},
    {assignment, ASSIGNMENT},
};

const std::vector<std::pair<TokenType, std::wstring>> TYPE_DATA_
{
    {number_datatype, NUMBER},
    {string_datatype, STRING},
    {character_datatype, CHARACTER},
};



[[nodiscard]] bool IsDigit(wchar_t number);
[[nodiscard]] bool IsSpace(wchar_t _ch);
[[nodiscard]] bool IsSymbol(wchar_t _ch);
[[nodiscard]] bool IsLetterOrDigit(wchar_t _ch);
[[nodiscard]] bool isQuote(wchar_t ch);

[[nodiscard]] bool Is_func_test(int to, int from, wchar_t ch);
[[nodiscard]] bool Is_func_test(const std::pair<int, int>& p, wchar_t ch);

[[nodiscard]] std::wstring ConvertString(const std::string& string);

[[nodiscard]] std::wstring test_st(const std::wstring& _input, int& position,
    const std::function<bool(wchar_t)>& func);

[[nodiscard]] std::function<bool(const wchar_t&)> test_bind(wchar_t ch, bool is);
[[nodiscard]] std::function<bool(const std::wstring&)> test_func_auto(
    const std::wstring& sb);

std::shared_ptr<IToken> Factory_func(TokenType token, const std::wstring& value);

void remove_nullptr_vec(std::vector<std::shared_ptr<IToken>>& tokens);

bool test_func_check_class_token(const std::shared_ptr<IToken>& token);

template<typename T>
[[nodiscard]] std::wstring test_func_wstring(const T& t)
{
    std::wstring io;
    io = t;
    return io;
}

template<typename T>
[[nodiscard]] std::shared_ptr<IToken> test_func_(
    const std::vector<std::pair<TokenType, T>>& vec,
    const std::function<bool(const T&)>& func)
{
    for (const auto& [_token, ch] : vec)
        if (func(ch))
            return Factory_func(_token, test_func_wstring(ch));
    return Factory_func(none, NONE);
}

#endif //CONFIG_HPP
