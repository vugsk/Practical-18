
#ifndef CONFIG_HPP
#define CONFIG_HPP


#include <functional>
#include <string>

#include "TokenType.hpp"


#define TEST false
#define DEBUG false



namespace type_char_literals
{

static constexpr wchar_t COLON             = ':';
static constexpr wchar_t SEMICOLON         = ';';
static constexpr wchar_t ASSIGNMENT        = '=';
static constexpr wchar_t SPACE             = ' ';
static constexpr wchar_t ENTER             = '\n';
static constexpr wchar_t STRING_LITERAL    = '\"';
static constexpr wchar_t CHARACTER_LITERAL = '\'';

static const std::wstring END  = L"END";
static const std::wstring NONE = L"NONE";
static const std::wstring NUL  = L"NULL";

static const std::wstring NUMBER    = L"число";
static const std::wstring STRING    = L"строка";
static const std::wstring CHARACTER = L"символ";

static constexpr std::pair NUMBER_LITERAL = {45, 57};
static constexpr std::pair ALPHOVIT       = {1072, 1103};



static const std::vector<std::pair<TokenType, wchar_t>> TYPE_CHAR_
{
    {colon, COLON},
    {semicolon, SEMICOLON},
    {assignment, ASSIGNMENT},
};

static const std::vector<std::pair<TokenType, std::wstring>> TYPE_DATA_
{
    {number_datatype, NUMBER},
    {string_datatype, STRING},
    {character_datatype, CHARACTER},
};

}


namespace func_base
{

[[nodiscard]] bool IsDigit(wchar_t number);
[[nodiscard]] bool IsSpace(wchar_t _ch);
[[nodiscard]] bool IsSymbol(wchar_t _ch);
[[nodiscard]] bool IsLetterOrDigit(wchar_t _ch);
[[nodiscard]] bool isQuote(wchar_t ch);

[[nodiscard]] bool Is_func_test(int to, int from, wchar_t ch);
[[nodiscard]] bool Is_func_test(const std::pair<int, int>& p, wchar_t ch);

[[nodiscard]] std::wstring ConvertString(const std::string& string);

[[nodiscard]] std::function<bool(const wchar_t&)> test_bind(wchar_t ch, bool is);
[[nodiscard]] std::function<bool(const std::wstring&)> test_func_auto(
    const std::wstring& sb);

template<typename F>
auto test_func_bind_lamda(const F& func)
{
    return [func](int& p) { return func; };
}

}





#endif //CONFIG_HPP
