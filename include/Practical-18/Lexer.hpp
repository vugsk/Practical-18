#ifndef LEXER_HPP
#define LEXER_HPP

#include "ILexer.hpp"

class Lexer final : public ILexer
{
public:
    Lexer()                                  = default;
    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer() override                        = default;


protected:


private:

};

#endif //LEXER_HPP
