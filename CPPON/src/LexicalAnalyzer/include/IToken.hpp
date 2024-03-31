
#ifndef ITOKEN_HPP
#define ITOKEN_HPP

#include <cstdint>
#include <string>

enum class TokenType : int8_t;

class IToken
{
public:
    typedef std::wstring      value_type;
    typedef const value_type& ref_value_type;
    typedef const TokenType&  ref_token_type;

    virtual                              ~IToken() = default;
    [[nodiscard]] virtual ref_token_type getToken() const = 0;
    [[nodiscard]] virtual ref_value_type getValue() const = 0;
    [[nodiscard]] virtual const uint32_t& getLine()  const = 0;
};

#endif //ITOKEN_HPP
