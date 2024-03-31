
#include "Parser.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "IToken.hpp"


static constexpr bool operator==(const std::vector<std::shared_ptr<IToken>>& lhs,
                std::vector<std::vector<TokenType>>::const_reference rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    for (auto i = 0; i < lhs.size(); i++)
        if (lhs[i]->getToken() != rhs[i])
            return false;

    return true;
}

static bool operator==(const std::shared_ptr<IToken>& token,
    const TokenType& type)
{
    return token->getToken() == type;
}

static bool operator!=(const std::shared_ptr<IToken>& token,
    const TokenType& type)
{
    return token->getToken() != type;
}


static constexpr bool is_test_func_data_type(
    const std::vector<std::shared_ptr<IToken>>& line_tokens,
    const TokenType& type)
{
    return std::ranges::any_of(line_tokens, 
        [type](const auto& i)
    {
        return i->getToken() == type;
    });
}

static constexpr bool is_test_func_number(
    const std::vector<std::shared_ptr<IToken>>& line_tokens)
{
    return is_test_func_data_type(line_tokens, TokenType::number_datatype);
}

static constexpr bool is_test_func_string(
    const std::vector<std::shared_ptr<IToken>>& line_tokens)
{
    return is_test_func_data_type(line_tokens, TokenType::string_datatype);
}

static constexpr bool is_test_func_char(
    const std::vector<std::shared_ptr<IToken>>& line_tokens)
{
    return is_test_func_data_type(line_tokens, TokenType::character_datatype);
}

static constexpr uint32_t find_test_func(
    const std::vector<std::shared_ptr<IToken>>& tokens,
    const TokenType& type)
{
    for (int i = 0; i < tokens.size(); i++)
        if (tokens[i]->getToken() == type)
            return i;

    return -1;
}

[[nodiscard]] static constexpr bool test_func_is_num(uint32_t index,
    const std::vector<std::shared_ptr<IToken>>& tokens)
{
    if (index == -1) return true;
    if (tokens[index - 1] != TokenType::assignment) return true;
    
    if (tokens[index + 1] != TokenType::semicolon && 
        tokens[index + 1] != TokenType::comma) return true;

    if (tokens[index - 3] != TokenType::colon) return true;

    return false;
}

[[nodiscard]] static constexpr bool test_is_func(uint32_t index,
    const std::vector<std::shared_ptr<IToken>>& tokens, uint32_t& pos_err,
    TokenType data)
{
    if (test_func_is_num(index, tokens) || tokens[index - 2] != data)
    {
        std::wcout << tokens[index]->getValue() << '\n';
        pos_err = tokens[index]->getLine();
        return true;
    }
    return false;
}

static constexpr bool is_test_func_easy_data(
    const std::vector<std::shared_ptr<IToken>>& line_token)
{
    return is_test_func_number(line_token) ||
           is_test_func_string(line_token) ||
           is_test_func_char(line_token);
}


Parser::Parser(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    check_tokens(tokens);
    parse(tokens);
}

constexpr void Parser::parse(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    std::vector<std::shared_ptr<IToken>> line_tokens;
    for (const auto& i : tokens)
    {
        if (i->getValue() == L";")
        {
            if (is_test_func_easy_data(line_tokens))
            {
                std::wstring name = line_tokens[find_test_func(line_tokens,
                    TokenType::id)]->getValue();
                std::wstring type = line_tokens[find_test_func(line_tokens,
                    TokenType::colon) + 1]->getValue();
                uint32_t line = line_tokens.front()->getLine();
                std::wstring value = line_tokens[find_test_func(line_tokens,
                    TokenType::assignment) + 1]->getValue();

                _nodes.push_back(std::make_shared<Var>(name, value, type, line));
            }
            line_tokens.clear();
            continue;
        }
        line_tokens.push_back(i);
    }
}

void Parser::check_tokens(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    uint32_t index_literal_num = find_test_func(tokens, 
        TokenType::number_literal);
    uint32_t index_literal_str = find_test_func(tokens, 
        TokenType::string_literal);
    uint32_t index_literal_char = find_test_func(tokens, 
        TokenType::character_literal);

    uint32_t position_err = 0;
    if (test_is_func(index_literal_num, tokens, position_err, 
            TokenType::number_datatype) ||
        test_is_func(index_literal_str, tokens, position_err, 
            TokenType::string_datatype) ||
        test_is_func(index_literal_char, tokens, position_err, 
            TokenType::character_datatype))
    {
        std::wcout << "err: " << position_err << '\n';
        exit(EXIT_FAILURE);
    }
}

// std::any Parser::test_func_lol(const std::wstring& key) const
// {
//     for (auto i : _tokens_set)
//     {
//         if (i.front()->getValue() == key)
//         {
//             if (is_test_func_number(i))
//                 return std::stoi(i[find_test_func(i,
//                     TokenType::number_literal)]->getValue());
//
//             if (is_test_func_string(i))
//                 return i[find_test_func(i,
//                     TokenType::string_literal)]->getValue();
//
//             if (is_test_func_char(i))
//                 return i[find_test_func(i,
//                     TokenType::character_literal)]->getValue()[1];
//         }
//     }
//     return 0;
// }

bool is_test_func_struct() { return false; }
