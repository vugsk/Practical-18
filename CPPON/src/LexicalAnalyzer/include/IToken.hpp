
#ifndef ITOKEN_HPP
#define ITOKEN_HPP

#include <string>

struct TokenType;

class IToken
{
public:
    virtual ~IToken() = default;
    [[nodiscard]] virtual const TokenType& getToken() const = 0;
    [[nodiscard]] virtual const std::wstring& getValue() const = 0;
};

#endif //ITOKEN_HPP
