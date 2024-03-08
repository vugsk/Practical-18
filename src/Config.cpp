
#include "Config.hpp"

#include <codecvt>
#include <locale>
#include <memory>


using namespace type_char_literals;

bool func_base::Is_func_test(const int to, const int from, const wchar_t ch)
{
    for (auto i = to; i < from + 1; i++)
        if (i == ch)
            return true;
    return false;
}

bool func_base::Is_func_test(const std::pair<int, int>& p, const wchar_t ch)
{
    return Is_func_test(p.first, p.second, ch);
}

bool func_base::IsDigit(const wchar_t number)
{
    return Is_func_test(45, 57, number);
}

bool func_base::IsSpace(const wchar_t _ch)
{
    return _ch == SPACE;
}

bool func_base::IsSymbol(const wchar_t _ch)
{
    return Is_func_test(1072, 1103, _ch);
}

bool func_base::IsLetterOrDigit(const wchar_t _ch)
{
    return IsDigit(_ch) || IsSymbol(_ch);
}

bool func_base::isQuote(const wchar_t ch)
{
    return ch == CHARACTER_LITERAL || ch == STRING_LITERAL;
}

std::wstring func_base::ConvertString(const std::string& string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(string.c_str());
    return wtext;
}

std::function<bool(const wchar_t&)> func_base::test_bind(const wchar_t ch, const bool is)
{
    return [ch, is](const wchar_t i) -> bool
    {
        return is ? ch == i : ch != i;
    };
}

std::function<bool(const std::wstring&)> func_base::test_func_auto(const std::wstring& sb)
{
    return [sb](const std::wstring& i) -> bool
    {
        return std::ranges::equal(sb, i);
    };
}


