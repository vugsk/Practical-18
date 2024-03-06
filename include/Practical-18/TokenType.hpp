
#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

#include <vector>

enum class TokenType : short
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

static const std::vector TOKEN_TYPES
{
    TokenType::none,
    TokenType::colon,
    TokenType::semicolon,
    TokenType::assignment,
    TokenType::string_literal,
    TokenType::number_literal,
    TokenType::number_datatype,
    TokenType::string_datatype,
    TokenType::character_datatype,
    TokenType::id,
    TokenType::end,
};

#endif //TOKENTYPE_HPP
