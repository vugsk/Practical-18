
#include "Parser.hpp"

#include <iostream>

#include "IToken.hpp"

const std::vector<std::vector<TokenType>> Parser::_test_funcs
{
    {TokenType::id, TokenType::colon, TokenType::number_datatype,
            TokenType::assignment, TokenType::number_literal,
                TokenType::semicolon},

    {TokenType::id, TokenType::colon, TokenType::string_datatype,
            TokenType::assignment, TokenType::string_literal,
                TokenType::semicolon},

    {TokenType::id, TokenType::colon, TokenType::character_datatype,
            TokenType::assignment, TokenType::character_literal,
                TokenType::semicolon},
};


bool operator==(const std::vector<std::shared_ptr<IToken>>& lhs,
                std::vector<std::vector<TokenType>>::const_reference rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    for (auto i = 0; i < lhs.size(); i++)
        if (lhs[i]->getToken() != rhs[i])
            return false;

    return true;
}

Parser::Parser(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    parse(tokens);
    check_tokens();
}

void Parser::parse(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    std::vector<std::shared_ptr<IToken>> line_tokens;
    for (const auto& i : tokens)
    {
        if (i->getValue() == L";")
        {
            line_tokens.push_back(i);
            _tokens_set.insert(line_tokens);
            line_tokens.clear();
            continue;
        }
        line_tokens.push_back(i);
    }
}

void Parser::check_tokens() const
{
    std::shared_ptr<IToken> _test_token = nullptr;
    for (auto& i : _tokens_set) {
        auto found = false;
        for (const auto& _test_func : _test_funcs)
            if (i == _test_func)
                found = true;
        if (!found)
            _test_token = i.front();
    }

    if (_test_token)
    {
        std::wcout << "Error: is not a test function. position: "
            << _test_token->getLine();
        exit(EXIT_FAILURE);
    }
}


bool is_test_func_data_type(
    const std::vector<std::shared_ptr<IToken>>& line_tokens,
    const TokenType& type)
{
    for (const auto& i : line_tokens)
        if (i->getToken() == type)
            return true;
    return false;
}

bool Parser::is_test_func_struct() { return false; }

bool Parser::is_test_func_number(
    const std::vector<std::shared_ptr<IToken>>& line_tokens)
{
    return is_test_func_data_type(line_tokens, TokenType::number_datatype);
}

bool Parser::is_test_func_string(
    const std::vector<std::shared_ptr<IToken>>& line_tokens)
{
    return is_test_func_data_type(line_tokens, TokenType::string_datatype);
}

bool Parser::is_test_func_char(
    const std::vector<std::shared_ptr<IToken>>& line_tokens)
{
    return is_test_func_data_type(line_tokens, TokenType::character_datatype);
}
