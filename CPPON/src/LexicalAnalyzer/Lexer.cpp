
#include "Lexer.hpp"

#include <algorithm>
#include <memory>
#include <memory>

#include <Token.hpp>
#include <TypeToken.hpp>

const char         Lexer::SPACE        = ' ';
const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;


Lexer::Lexer(std::wstring code)
    : _inputCode(std::move(code)) {}


std::vector<Lexer::tokenPointer> Lexer::lexicalCodeAnalysis()
{
    while (_position >= _inputCode.length())
    {



    }

    _tokens.push_back(createrToken(END, END.value));
    return _tokens;
}


std::shared_ptr<IToken> Lexer::createrToken(TokenType token_type,
    const std::wstring& value)
{
    return std::make_shared<Token>(token_type, _position, value);
}

std::shared_ptr<IToken> Lexer::test_func_operator()
{



    return {};
}

std::shared_ptr<IToken> Lexer::test_func_literal()
{
    return {};
}

std::shared_ptr<IToken> Lexer::test_func_data_type()
{
    return {};
}





