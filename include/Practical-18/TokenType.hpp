
#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

enum class TokenType
{
    COLON,          // двоеточие
    SEMICOLON,      // точка с запятой
    ASSIGNMENT,     // присваиваивание


    STRING_LITERAL, // кавычки
    NUMBER_LITERAL,


    NUMBER_DATATYPE,
    STRING_DATATYPE,
    CHARACTER_DATATYPE,
    ID,


    END,
};

#endif //TOKENTYPE_HPP
