
#include "Lexer.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <memory>

#include <Token.hpp>
#include <TypeToken.hpp>

const char         Lexer::SPACE        = ' ';
const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;


Lexer::Lexer(std::wstring code)
    : _inputCode(std::move(code))
    , _position(0) {}


std::vector<Lexer::tokenPointer> Lexer::lexicalCodeAnalysis()
{


    _tokens.push_back(createrToken(END, END.value));
    return _tokens;
}


std::shared_ptr<IToken> Lexer::createrToken(TokenType token_type,
    const std::wstring& value)
{
    return std::make_shared<Token>(token_type, value);
}





