
#ifndef ITOKEN_HPP
#define ITOKEN_HPP

#include <string>

#include "TokenType.hpp"

class IToken {
public:
    virtual                            ~IToken() = default;
    [[nodiscard]] virtual TokenType    getToken() const = 0;
    [[nodiscard]] virtual std::wstring getValue() const = 0;
};



#endif //ITOKEN_HPP
