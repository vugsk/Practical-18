
#include "Lexer.hpp"

#include <algorithm>
#include <memory>

#include <Token.hpp>
#include <TypeToken.hpp>

const char         Lexer::SPACE        = ' ';
const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;


Lexer::Lexer(std::wstring code) : _inputCode(std::move(code)) {}

std::vector<Lexer::tokenPointer> Lexer::lexicalCodeAnalysis()
{
    while (_position <= _inputCode.length() - 1)
    {
        for (const auto i : TOKEN_OPERATORS)
            if (i.value[0] == _inputCode[_position])
                _tokens.push_back(createrToken(i, i.value));

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
        if (i.tokenType == TOKEN_LITERALS[2].tokenType)
        {

        }
        else if (i.value[0] == _inputCode[_position])
        {

        }
    }
    return {};
}

std::shared_ptr<IToken> Lexer::test_func_data_type()
{
    return {};
}





