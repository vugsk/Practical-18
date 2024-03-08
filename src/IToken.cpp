
#include "IToken.hpp"

#include "Token.hpp"

using namespace itoken;
using namespace type_char_literals;

bool func_itoken::test_if_none_token(const std::shared_ptr<IToken>& token)
{
    return token->getToken() != none || token->getValue() != NONE;
}

bool func_itoken::test_if_null_token(const std::shared_ptr<IToken>& token,
    const std::wstring& value_if)
{
    return token->getToken() != null || token->getValue() != value_if;
}


std::shared_ptr<IToken> func_itoken::test_func_string_leteral(
    const std::wstring& value)
{
    return test_func_factory(string_literal, value);
}

std::shared_ptr<IToken> func_itoken::test_func_number_leteral(
    const std::wstring& value)
{
    return test_func_factory(number_literal, value);
}

std::shared_ptr<IToken> func_itoken::test_func_id(const std::wstring& value)
{
    return test_func_factory(id, value);
}

std::shared_ptr<IToken> func_itoken::test_func_none(const std::wstring& value)
{
    return test_func_factory(none, value);
}

std::shared_ptr<IToken> func_itoken::test_func_end(const std::wstring& value)
{
    return test_func_factory(end, value);
}

std::shared_ptr<IToken> func_itoken::test_func_null(const std::wstring& value)
{
    return test_func_factory(null, value);
}