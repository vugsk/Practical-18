
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
typedef std::shared_ptr<itoken::IToken> tokenPtr;

bool test_if_none_token(const tokenPtr& token);
bool test_if_null_token(const tokenPtr& token,
    const std::wstring& value_if = lexicon_cppon::NUL);

tokenPtr test_func_string_leteral(const std::wstring& value);
tokenPtr test_func_number_leteral(const std::wstring& value);
tokenPtr test_func_id(const std::wstring& value);
tokenPtr test_func_none(const std::wstring& value = lexicon_cppon::NONE);
tokenPtr test_func_end(const std::wstring& value = lexicon_cppon::END);
tokenPtr test_func_null(const std::wstring& value = lexicon_cppon::NUL);

}

#endif //ITOKEN_HPP
