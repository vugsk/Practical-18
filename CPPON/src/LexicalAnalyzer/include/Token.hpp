
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <IToken.hpp>

class Token final : public IToken
{
public:
    Token(const Token& other)                = delete;
    Token(Token&& other) noexcept            = delete;
    Token& operator=(const Token& other)     = delete;
    Token& operator=(Token&& other) noexcept = delete;

    Token(TokenType token, const std::wstring& value)
        : _token(token), _value(value) {}
    Token(TokenType token, const wchar_t value)
        : _token(token)
    {
        _value = value;
    }

    ~Token() override = default;

    [[nodiscard]] TokenType           getToken() const override
    {
        return _token;
    }

    [[nodiscard]] const std::wstring& getValue() const override
    {
        return _value;
    }

private:
    TokenType _token;
    std::wstring _value;
};


#endif //TOKEN_HPP
