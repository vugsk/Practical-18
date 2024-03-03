
#include "Config.hpp"

#include <codecvt>
#include <locale>

bool IsDigit(const wchar_t number)
{
    for(const auto i : L"1234567890")
        if (number == i)
            return true;
    return false;
}

bool IsSpace(const wchar_t _ch)
{
    return _ch == SPACE;
}

bool IsSymbol(const wchar_t _ch)
{
    for(const auto i : L"йцукенгшщзхъфывапролджэячсмитьбю")
        if (i == _ch)
            return true;
    return false;
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
