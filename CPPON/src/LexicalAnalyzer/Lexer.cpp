
#include "Lexer.hpp"

#include <algorithm>
#include <codecvt>
#include <memory>
#include <regex>

#include <Token.hpp>
#include <TypeToken.hpp>

const char         Lexer::SPACE        = ' ';
const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;

std::string ConvertWstring(const std::wstring& string)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(string);
}

std::wstring ConvertString(const std::string& string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(string.c_str());
}

Lexer::Lexer(std::wstring code) : _inputCode(std::move(code)) {}

std::vector<Lexer::tokenPointer> Lexer::lexicalCodeAnalysis()
{
    while (_position <= static_cast<unsigned>(_inputCode.length()) - 1)
    {
        for (const auto i : TOKEN_OPERATORS)
            if (i.value[0] == _inputCode[_position])
                _tokens.push_back(createrToken(i, i.value));

        for (auto i : TOKEN_LITERALS)
        {
            std::smatch m;
            std::string s;
            std::regex_search(s, m, std::regex(ConvertWstring(i.value)));
            _tokens.push_back(createrToken(i, ConvertString(m[0].str().c_str())));
        }


        _position++;
    }

    _tokens.push_back(createrToken(END, END.value));
    return _tokens;
}


std::shared_ptr<IToken> Lexer::createrToken(TokenType token_type,
    const std::wstring& value)
{
    return std::make_shared<Token>(token_type, _position, value);
}

// * thing
std::shared_ptr<IToken> Lexer::test_func_operator()
{
    for (const auto i : TOKEN_OPERATORS)
        if (i.value[0] == _inputCode[_position])
            return createrToken(i, i.value);
    return createrToken(NUL, NUL.value);
}

std::shared_ptr<IToken> Lexer::test_func_literal()
{
    for (auto i : TOKEN_LITERALS)
    {
        std::smatch m;
        std::string s;
        std::regex_search(s, m, std::regex(ConvertWstring(i.value)));

    }
    return {};
}

std::shared_ptr<IToken> Lexer::test_func_data_type()
{
    return {};
}





