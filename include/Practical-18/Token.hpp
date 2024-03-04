
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "IToken.hpp"


class Token final : public IToken {
public:
    // Token(const Token& other)                = delete;
    // Token(Token&& other) noexcept            = delete;
    // Token& operator=(const Token& other)     = delete;
    // Token& operator=(Token&& other) noexcept = delete;
    ~Token() override = default;
    Token(TokenType token, std::wstring value);

    [[nodiscard]] TokenType getToken() const override;
    [[nodiscard]] std::wstring getValue() const override;

private:
    TokenType    _token;
    std::wstring _value;
};



#endif //TOKEN_HPP
