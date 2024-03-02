
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "IToken.hpp"

class Token final : IToken {
public:
    Token();
    Token(const Token& other)                = delete;
    Token(Token&& other) noexcept            = delete;
    Token& operator=(const Token& other)     = delete;
    Token& operator=(Token&& other) noexcept = delete;
    ~Token() override                        = default;



protected:


private:

};



#endif //TOKEN_HPP
