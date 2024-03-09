
#include "include/Token.hpp"

using namespace token_;

Token::Token(const TokenType token, std::wstring value)
    : _token(token), _value(std::move(value)) {}

Token::Token(const TokenType token, const wchar_t value)
    : _token(token)
{
    _value = value;
}

TokenType Token::getToken() const
{
    return _token;
}

std::wstring Token::getValue() const
{
    return _value;
}
