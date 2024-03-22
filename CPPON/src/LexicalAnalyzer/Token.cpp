
#include "Token.hpp"

#include <utility>

Token::Token(std::wstring value, std::pair<uint32_t, uint32_t> location)
    : _location(std::move(location))
{
    _value = std::move(value);
    _token = test_func_token();
}

const TokenType& Token::getToken() const
{
    return _token;
}

const std::wstring& Token::getValue() const
{
    return _value;
}

const std::pair<uint32_t, uint32_t>& Token::getLine() const
{
    return _location;
}
