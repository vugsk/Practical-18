
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <vector>

#include "IToken.hpp"


enum class TokenType : int8_t
{
    none = -1,
    null = 0,
    end = 1,
    id,

    colon,
    semicolon,
    assignment,
    comma,
    left_bracket,
    right_bracket,

    string_literal,
    number_literal,
    character_literal,

    number_datatype,
    string_datatype,
    character_datatype,
};

typedef std::pair<TokenType, std::wstring> token_pair;
static const std::vector<token_pair> TOKENS
{
        {TokenType::colon, L":"},
        {TokenType::semicolon, L";"},
        {TokenType::assignment, L"="},
        {TokenType::left_bracket, L"("},
        {TokenType::right_bracket, L")"},
        {TokenType::comma, L","},
        {TokenType::string_literal, L"\""},
        {TokenType::character_literal, L"\'"},
        {TokenType::number_literal, L"0-9"},

        {TokenType::string_datatype, L"строка"},
        {TokenType::number_datatype, L"число"},
        {TokenType::character_datatype, L"символ"},

        {TokenType::id, L"ID"},
};

static const token_pair NONE = {TokenType::none, L"NONE"};
static const token_pair NUL  = {TokenType::null, L"NULL"};
static const token_pair END  = {TokenType::end, L"END"};


class Token final : public IToken
{
public:
    Token(const Token& other)                = delete;
    Token(Token&& other) noexcept            = delete;
    Token& operator=(const Token& other)     = delete;
    Token& operator=(Token&& other) noexcept = delete;
    ~Token() override                        = default;

    explicit Token(std::wstring value, location location = EMPTY_LOCATION);

    [[nodiscard]] constexpr ref_token_type getToken() const override;
    [[nodiscard]] constexpr ref_value_type getValue() const override;
    [[nodiscard]] constexpr ref_location   getLine() const override;

protected:
    constexpr TokenType checkValueType();

private:
    static constinit const location EMPTY_LOCATION;

    TokenType  _token;
    value_type _value;
    location   _location;

};


#endif //TOKEN_HPP
