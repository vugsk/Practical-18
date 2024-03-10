
#ifndef ITOKEN_HPP
#define ITOKEN_HPP

#include <string>

enum TokenType : short;

class IToken
{
public:
    virtual ~IToken() = default;
    [[nodiscard]] virtual TokenType getToken() const = 0;
    [[nodiscard]] virtual const std::wstring& getValue() const = 0;
};

#endif //ITOKEN_HPP
