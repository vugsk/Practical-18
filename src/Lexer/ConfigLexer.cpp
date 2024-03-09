
#include "include/ConfigLexer.hpp"

#include <codecvt>
#include <locale>


bool IsQuote(const wchar_t ch)
{
    return ch == CHARACTER_LITERAL || ch == STRING_LITERAL;
}

std::wstring ConvertString(const std::string& string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(string.c_str());
    return wtext;
}