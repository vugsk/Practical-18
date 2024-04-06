
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "IToken.hpp"

class Token final : public IToken
{
public:
    Token(const Token& other)                = delete;
    Token(Token&& other) noexcept            = delete;
    Token& operator=(const Token& other)     = delete;
    Token& operator=(Token&& other) noexcept = delete;
    ~Token() override                        = default;

    explicit Token(std::wstring value, uint32_t location = 0);

    [[nodiscard]] ref_token_type  getToken() const override;
    [[nodiscard]] ref_value_type  getValue() const override;
    [[nodiscard]] const uint32_t& getLine() const override;

protected:
    constexpr TokenType checkValueType();

private:
    TokenType  _token;
    value_type _value;
    uint32_t   _line;

};


#endif //TOKEN_HPP
