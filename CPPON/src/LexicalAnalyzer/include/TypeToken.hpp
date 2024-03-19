
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
    {L"STRING_LITERAL", LR"("[а-я|А-Я|a-z|A-Z]*")"},
    {L"CHARACTER_LITERAL", LR"('[а-я|А-Я|a-z|A-Z]')"},
    {L"NUMBER_LITERAL", LR"([0-9]*)"},
};

static const std::vector<TokenType> TOKEN_DATA_TYPES
{
    {L"STRING_DATATYPE", LR"(строка)"},
    {L"NUMBER_DATATYPE", LR"(число)"},
    {L"CHARACTER_DATATYPE", LR"(символ)"},
};

static constexpr TokenType ID = {L"ID", LR"([а-я|А-Я|a-z|A-Z|0-9]*)"};
static constexpr TokenType NONE = {L"NONE", L"NONE"};
static constexpr TokenType NUL = {L"NULL", L"NULL"};
static constexpr TokenType END = {L"END", L"END"};


#endif //TYPETOKEN_HPP
