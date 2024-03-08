
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <functional>
#include <memory>

#include "Token.hpp"
#include "TokenType.hpp"

#define TEST false
#define DEBUG false



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

void remove_nullptr_vec(std::vector<std::shared_ptr<IToken>>& tokens);
bool test_func_check_class_token(const std::shared_ptr<IToken>& token);
bool test_if_none_token(const std::shared_ptr<IToken>& token);
bool test_if_null_token(const std::shared_ptr<IToken>& token,
    const std::wstring& value_if = NUL);


std::shared_ptr<IToken> test_func_string_leteral(const std::wstring& value);
std::shared_ptr<IToken> test_func_number_leteral(const std::wstring& value);
std::shared_ptr<IToken> test_func_id(const std::wstring& value);
std::shared_ptr<IToken> test_func_none(const std::wstring& value = NONE);
std::shared_ptr<IToken> test_func_end(const std::wstring& value = END);
std::shared_ptr<IToken> test_func_null(const std::wstring& value = NUL);

template<typename T>
std::shared_ptr<IToken> test_func_factory(const TokenType token, const T& value)
{
    for (const auto i : TOKEN_TYPES)
        if (token == i)
            return std::make_shared<Token>(token, value);
    return test_func_none();
}

template<typename T>
std::shared_ptr<IToken> test_func_(
        const std::vector<std::pair<TokenType, T>>& vec,
        const std::function<bool(const T&)>& func,
        const std::shared_ptr<IToken>& default_return = test_func_none())
{
    for (const auto& [_token, ch] : vec)
        if (func(ch))
            return test_func_factory(_token, ch);
    return default_return;
}

template<typename F>
auto test_func_bind_lamda(const F& func)
{
    return [func](int& p) { return func; };
}

#endif //CONFIG_HPP
