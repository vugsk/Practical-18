
#include "Config.hpp"

#include <algorithm>
#include <codecvt>
#include <locale>

bool IsDigit(const wchar_t number)
{
    return std::ranges::any_of(NUMBER_LITERAL, [number](const wchar_t i)
    {
        return number == i;
    });
}

bool IsSpace(const wchar_t _ch)
{
    return _ch == SPACE;
}

bool IsSymbol(const wchar_t _ch)
{
    return std::ranges::any_of(ALPHOVIT, [_ch](const wchar_t i)
    {
        return _ch == i;
    });
}

bool IsLetterOrDigit(const wchar_t _ch)
{
    return IsDigit(_ch) || IsSymbol(_ch);
}

bool is_func(const wchar_t ch)
{
    return ch == STRING_LITERAL.first || ch == STRING_LITERAL.second;
}

bool isEnter(const wchar_t ch)
{
    return ch == ENTER;
}

bool isQuote(const wchar_t ch)
{
    return ch == STRING_LITERAL.first || ch == STRING_LITERAL.second;
}

bool is_func_E_Q_S(const wchar_t ch)
{
    return IsSpace(ch) || isEnter(ch) || isQuote(ch);
}

bool test_func_bool(const wchar_t ch, const wchar_t i, const bool is)
{
    return is ? ch == i : ch != i;
}

std::wstring ConvertString(const std::string& string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(string.c_str());
    return wtext;
}

std::wstring test_st(const std::wstring& _input, int& position,
    const std::function<bool(wchar_t)>& func)
{
    std::wstring sb;
    while (func(_input[position]))
        sb.push_back(_input[position++]);
    return sb;
}

std::function<bool(const wchar_t&)> test_bind(const wchar_t ch, const bool is)
{
    return [ch, is](const wchar_t i)
    {
        return test_func_bool(i, ch, is);
    };
}
