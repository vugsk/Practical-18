
#include "Token.hpp"

#include "ConfigLexer.hpp"

#include <algorithm>
#include <cwctype>
#include <iostream>
#include <utility>

using std::next;
using std::move;
using std::wstring;
using std::ranges::all_of;

constinit const Token::location Token::EMPTY_LOCATION = {0, 0};

template<typename F>
constexpr bool test_func(const wstring& str, const F&& func)
{
    return func(str.front()) && func(str.back());
}


Token::Token(value_type value, location location)
    : _location(move(location))
{
    _value = move(value);
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

    if (test_func<bool(const wchar_t&)>(_value, IsDoubleQuote))
        return TokenType::string_literal;

     if (test_func<bool(const wchar_t&)>(_value, IsOneQuote))
        return TokenType::character_literal;

    if (all_of(_value, iswdigit) && _value.front() != L'-')
        return TokenType::number_literal;

    if (all_of(next(_value.begin()), _value.end(), iswdigit))
        return TokenType::number_literal;

    return TokenType::id;
}
