
#ifndef ITOKEN_HPP
#define ITOKEN_HPP

#include <memory>

#include "Config.hpp"


namespace itoken
{

class IToken
{
public:
    virtual                            ~IToken() = default;
    [[nodiscard]] virtual TokenType    getToken() const = 0;
    [[nodiscard]] virtual std::wstring getValue() const = 0;
};

}

namespace func_itoken
{

bool test_if_none_token(const std::shared_ptr<itoken::IToken>& token);
bool test_if_null_token(const std::shared_ptr<itoken::IToken>& token,
    const std::wstring& value_if = type_char_literals::NUL);

std::shared_ptr<itoken::IToken> test_func_string_leteral(const std::wstring& value);
std::shared_ptr<itoken::IToken> test_func_number_leteral(const std::wstring& value);
std::shared_ptr<itoken::IToken> test_func_id(const std::wstring& value);
std::shared_ptr<itoken::IToken> test_func_none(const std::wstring& value =
    type_char_literals::NONE);
std::shared_ptr<itoken::IToken> test_func_end(const std::wstring& value =
    type_char_literals::END);
std::shared_ptr<itoken::IToken> test_func_null(const std::wstring& value =
    type_char_literals::NUL);

}

#endif //ITOKEN_HPP
