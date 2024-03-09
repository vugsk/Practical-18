
#ifndef CONFIG_HPP
#define CONFIG_HPP


#include <functional>
#include <string>

#include "TokenType.hpp"


#define TEST false
#define DEBUG false



namespace lexicon_cppon
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



static const std::vector<std::pair<TokenType, wchar_t>> OPERATORS
{
    {colon, COLON},
    {semicolon, SEMICOLON},
    {assignment, ASSIGNMENT},
};

static const std::vector<std::pair<TokenType, std::wstring>> DATA_TYPES
{
    {number_datatype, NUMBER},
    {string_datatype, STRING},
    {character_datatype, CHARACTER},
};

} //lexicon_cppon


namespace standard_functions
{

[[nodiscard]] bool IsQuote(wchar_t ch);

[[nodiscard]] std::wstring ConvertString(const std::string& string);

template<typename F>
auto test_func_bind_lamda(const F& func)
{
    return [func](int& p) { return func; };
}

} //standard_functions





#endif //CONFIG_HPP
