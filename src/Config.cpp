
#include "Config.hpp"

#include <algorithm>
#include <codecvt>
#include <locale>

bool IsDigit(const wchar_t number)
{
    return std::ranges::any_of(L"1234567890", [number](const wchar_t i)
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
    return std::ranges::any_of(L"йцукенгшщзхъфывапролджэячсмитьбю",
        [_ch](const wchar_t i)
    {
        return _ch == i;
    });
}

bool IsLetterOrDigit(const wchar_t _ch)
{
    return IsDigit(_ch) || IsSymbol(_ch);
}

[[nodiscard]] std::wstring ConvertString(const std::string& string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(string.c_str());
    return wtext;
}
