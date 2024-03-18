
#ifndef TYPETOKEN_HPP
#define TYPETOKEN_HPP

#include <vector>

struct TokenType
{
    const wchar_t* tokenType;
    const wchar_t* value;
};

static const std::vector<TokenType> TOKEN_OPERATORS
{
    {L"COLON", L":"},
    {L"SEMICOLON", L";"},
    {L"ASSIGMENT", L"="},
};

static const std::vector<TokenType> TOKEN_LITERALS
{
    {L"STRING_LITERAL", L"\""},
    {L"CHARACTER_LITERAL", L"\'"},
    {L"NUMBER_LITERAL", L"0-9"},
};

static const std::vector<TokenType> TOKEN_DATA_TYPES
{
    {L"STRING_DATATYPE", L"строка"},
    {L"NUMBER_DATATYPE", L"число"},
    {L"CHARACTER_DATATYPE", L"символ"},
    {L"ID", L"а-я && 0-9"},
};

static constexpr TokenType NONE = {L"NONE", L"NONE"};
static constexpr TokenType NUL = {L"NULL", L"NULL"};
static constexpr TokenType END = {L"END", L"END"};


#endif //TYPETOKEN_HPP
