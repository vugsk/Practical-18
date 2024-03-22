
#ifndef TOKEN_HPP
#define TOKEN_HPP

// #define TEST_TOKEN
#define DEBUG_TOKEN


#ifdef DEBUG_TOKEN
    #include <iostream>
#endif

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

    string_literal,
    number_literal,

    number_datatype,
    string_datatype,
    character_datatype,
};

static const std::vector<std::pair<TokenType, std::wstring>> TOKEN_TYPES
{
        {TokenType::colon, L":"},
        {TokenType::semicolon, L";"},
        {TokenType::assignment, L"="},
        // {L"LEFT_BRACKET", L"("},
        // {L"RIGHT_BRACKET", L")"},
        // {L"COMMA", L","},
        {TokenType::string_literal, L"\""},
        // {L"CHARACTER_LITERAL", L"\'"},
        {TokenType::number_literal, L"0-9"},

        {TokenType::string_datatype, L"строка"},
        {TokenType::number_datatype, L"число"},
        {TokenType::character_datatype, L"символ"},

        {TokenType::id, L"ID"},
};

class Token final : public IToken
{
public:
    Token(const Token& other)                = delete;
    Token(Token&& other) noexcept            = delete;
    Token& operator=(const Token& other)     = delete;
    Token& operator=(Token&& other) noexcept = delete;
    ~Token() override = default;

    Token(std::wstring value, std::pair<uint32_t, uint32_t> location);

    [[nodiscard]] const TokenType& getToken() const override;
    [[nodiscard]] const std::wstring& getValue() const override;
    [[nodiscard]] const std::pair<uint32_t, uint32_t>& getLine() const override;

    #ifdef DEBUG_TOKEN
        void printDebug()
        {
            std::wcout << "Token: "
                       << _value << " | "
                       << static_cast<int8_t>(_token) << " | "
                       << _location.first << " | "
                       << _location.second << '\n';
        }
    #endif

protected:
    // ! doing
    TokenType test_func_token()
    {
        for (auto [fst, snd] : TOKEN_TYPES)
        {
            if (snd == _value)
                return fst;
        }
        return TokenType::id;
    }

private:
    TokenType _token;
    std::wstring _value;
    std::pair<uint32_t, uint32_t> _location;
};


#endif //TOKEN_HPP
