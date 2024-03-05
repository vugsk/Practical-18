
#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

enum TokenType : short
{
    none = -1,
    colon = 0,          // двоеточие
    semicolon,      // точка с запятой
    assignment,     // присваиваивание


    string_literal, // кавычки
    number_literal,


    number_datatype,
    string_datatype,
    character_datatype,
    id,


    end,

};

constexpr unsigned short SIZE_TOKEN_TYPES = 10;
constexpr TokenType TOKEN_TYPES[SIZE_TOKEN_TYPES]
{
    colon,
    semicolon,
    assignment,
    string_literal,
    number_literal,
    number_datatype,
    string_datatype,
    character_datatype,
    id,
    end,
};

#endif //TOKENTYPE_HPP
