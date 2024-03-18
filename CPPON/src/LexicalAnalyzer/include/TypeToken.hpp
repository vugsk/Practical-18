
#ifndef TYPETOKEN_HPP
#define TYPETOKEN_HPP

struct TokenType
{
    const wchar_t* tokenType;
    const wchar_t* value;
};

static constexpr unsigned short SIZE_ARRAY_TOKEN_OPERATORS = 3;
static constexpr TokenType TOKEN_OPERATORS[SIZE_ARRAY_TOKEN_OPERATORS]
{
    {L"COLON", L":"},
    {L"SEMICOLON", L";"},
    {L"ASSIGMENT", L"="},
};

static constexpr unsigned short SIZE_ARRAY_TOKEN_LITERALS = 3;
static constexpr TokenType TOKEN_LITERALS[SIZE_ARRAY_TOKEN_LITERALS]
{
    {L"STRING_LITERAL", L"\""},
    {L"CHARACTER_LITERAL", L"\'"},
    {L"NUMBER_LITERAL", L"0-9"},
};

static constexpr unsigned short SIZE_ARRAY_TOKEN_DATA_TYPES = 4;
static constexpr TokenType TOKEN_DATA_TYPES[SIZE_ARRAY_TOKEN_DATA_TYPES]
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
