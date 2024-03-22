
#ifndef TYPETOKEN_HPP
#define TYPETOKEN_HPP

#include <string>
#include <vector>

struct TokenType_
{
    const wchar_t* tokenType;
    const wchar_t* value;
};

static const std::vector<std::pair<std::wstring, std::wstring>> TOKEN_TYPES
{
    {L"COLON", L":"},
    {L"SEMICOLON", L";"},
    {L"ASSIGMENT", L"="},
    {L"LEFT_BRACKET", L"("},
    {L"RIGHT_BRACKET", L")"},
    {L"COMMA", L","},
    {L"STRING_LITERAL", L"\""},
    {L"CHARACTER_LITERAL", L"\'"},
    {L"NUMBER_LITERAL", L"0-9"},

    {L"STRING_DATATYPE", L"строка"},
    {L"NUMBER_DATATYPE", L"число"},
    {L"CHARACTER_DATATYPE", L"символ"},

    {L"ID", L"ID"},
    {L"NONE", L"NONE"},
    {L"NULL", L"NULL"},
    {L"END", L"END"}
};

static const std::vector<TokenType_> TOKEN_LITERALS
{
    {L"STRING_LITERAL", L"\""},
    {L"CHARACTER_LITERAL", L"\'"},
    {L"NUMBER_LITERAL", L"0-9"},
};

static const std::vector<TokenType_> TOKEN_DATA_TYPES
{
    {L"STRING_DATATYPE", L"строка"},
    {L"NUMBER_DATATYPE", L"число"},
    {L"CHARACTER_DATATYPE", L"символ"},
};

static constexpr TokenType_ ID = {L"ID", L"ID"};
static constexpr TokenType_ NONE = {L"NONE", L"NONE"};
static constexpr TokenType_ NUL = {L"NULL", L"NULL"};
static constexpr TokenType_ END = {L"END", L"END"};


#endif //TYPETOKEN_HPP
