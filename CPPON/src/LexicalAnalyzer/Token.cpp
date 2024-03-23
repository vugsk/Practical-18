
#include "Token.hpp"

#include "ConfigLexer.hpp"

#ifdef DEBUG_TOKEN
    #include <iostream>
#endif

#include <algorithm>
#include <cwctype>
#include <utility>


Token::Token(value_type value, location location)
    : _location(std::move(location))
{
    _value = std::move(value);
    _token = checkValueType();
}

constexpr Token::ref_token_type Token::getToken() const
{
    return _token;
}

constexpr Token::ref_value_type Token::getValue() const
{
    return _value;
}

constexpr Token::ref_location Token::getLine() const
{
    return _location;
}

constexpr TokenType Token::checkValueType()
{
    for (const auto& [fst, snd] : TOKENS)
        if (snd == _value)
            return fst;

    if (IsDoubleQuote(_value.front()) && IsDoubleQuote(_value.back()))
        return TokenType::string_literal;

    if (IsOneQuote(_value.front()) && IsOneQuote(_value.back()))
        return TokenType::character_literal;

    if (std::ranges::count_if(_value, iswdigit) == _value.size())
        return TokenType::number_literal;

    return TokenType::id;
}
