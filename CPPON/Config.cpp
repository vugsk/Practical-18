
#include "Config.hpp"

#include <codecvt>
#include <locale>

std::wstring ConvertString(const std::string& string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(string.c_str());
}

std::string ConvertWstring(const std::wstring& string)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(string);
}

