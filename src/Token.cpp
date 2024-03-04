
#include "Token.hpp"

Token::Token(const TokenType token, std::wstring value)
    : _token(token), _value(std::move(value)) {}

TokenType Token::getToken() const
{
    return _token;
}

std::wstring Token::getValue() const
{
    return _value;
}
