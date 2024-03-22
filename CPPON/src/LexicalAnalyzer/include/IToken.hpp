
#ifndef ITOKEN_HPP
#define ITOKEN_HPP

#include <cstdint>
#include <string>

enum class TokenType : int8_t;

class IToken
{
public:
    virtual ~IToken() = default;
    [[nodiscard]] virtual const TokenType& getToken() const = 0;
    [[nodiscard]] virtual const std::wstring& getValue() const = 0;
    [[nodiscard]] virtual const std::pair<uint32_t, uint32_t>& getLine() const = 0;
};

#endif //ITOKEN_HPP
