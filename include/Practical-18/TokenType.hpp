
#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

#include <vector>

enum TokenType : short
{
    none = -1,
    null = 0,

    colon = 1,          // двоеточие
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

static const std::vector TOKEN_TYPES
{
    none,
    null,
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
