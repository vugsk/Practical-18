
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "IToken.hpp"

namespace token_
{

class Token final : public itoken::IToken
{
public:
    Token(const Token& other)                = delete;
    Token(Token&& other) noexcept            = delete;
    Token& operator=(const Token& other)     = delete;
    Token& operator=(Token&& other) noexcept = delete;
    ~Token() override                        = default;

    Token(TokenType token, std::wstring value);
    Token(TokenType token, wchar_t value);

    [[nodiscard]] TokenType getToken() const override;
    [[nodiscard]] std::wstring getValue() const override;

private:
    TokenType    _token;
    std::wstring _value;
};

}

template<typename T>
std::shared_ptr<itoken::IToken> test_func_factory(const TokenType token,
    const T& value)
{
    for (const auto i : TOKEN_TYPES)
        if (token == i)
            return std::make_shared<token_::Token>(token, value);
    return func_itoken::test_func_none();
}

#endif //TOKEN_HPP
