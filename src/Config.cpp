
#include "Config.hpp"

#include <codecvt>
#include <locale>


using namespace lexicon_cppon;

bool standard_functions::IsQuote(const wchar_t ch)
{
    return ch == CHARACTER_LITERAL || ch == STRING_LITERAL;
}

std::wstring standard_functions::ConvertString(const std::string& string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(string.c_str());
    return wtext;
}



