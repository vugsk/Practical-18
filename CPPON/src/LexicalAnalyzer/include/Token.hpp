
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "IToken.hpp"
#include "TypeToken.hpp"

class Token final : public IToken
{
public:
    Token(const Token& other)                = delete;
    Token(Token&& other) noexcept            = delete;
    Token& operator=(const Token& other)     = delete;
    Token& operator=(Token&& other) noexcept = delete;

    Token(const TokenType token, unsigned position,
        const std::wstring& value)
         : _token(token), _position(position), _value(value) {}

    [[nodiscard]] const TokenType& getToken() const override
    {
        return _token;
    }

    [[nodiscard]] const std::wstring& getValue() const override
    {
        return _value;
    }

    [[nodiscard]] unsigned short getPosition() const
    {
        return _position;
    }

private:
    TokenType _token;
    std::wstring _value;
    unsigned _position;
};


#endif //TOKEN_HPP
