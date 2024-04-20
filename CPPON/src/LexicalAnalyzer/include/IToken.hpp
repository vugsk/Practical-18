
#ifndef ITOKEN_HPP
#define ITOKEN_HPP

#include <cstdint>
#include <string>

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
    structe_datatype,
};

typedef std::pair<TokenType, const wchar_t*> token_pair;

static constexpr uint8_t SIZE_TOKENS_ARRAY = 15;
static const token_pair TOKENS_ARRAY[SIZE_TOKENS_ARRAY]
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
        {TokenType::structe_datatype, L"структура"},

        {TokenType::id, L"ID"},
        {TokenType::end, L"END"}
};

static const token_pair NONE = {TokenType::none, L"NONE"};
static const token_pair NUL  = {TokenType::null, L"NULL"};



class IToken
{
public:
    typedef std::wstring      value_type;
    typedef const value_type& ref_value_type;
    typedef const TokenType&  ref_token_type;

    virtual                              ~IToken() = default;
    [[nodiscard]] virtual ref_token_type getToken() const = 0;
    [[nodiscard]] virtual ref_value_type getValue() const = 0;
    [[nodiscard]] virtual const uint32_t& getLine()  const = 0;
};



#endif //ITOKEN_HPP
