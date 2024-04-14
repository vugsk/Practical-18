
#include "Parser.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include "IToken.hpp"
#include "Structe.hpp"
#include "Variable.hpp"


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

[[nodiscard]] static constexpr bool is_test_func_struct(
    const std::vector<std::shared_ptr<IToken>>& line_tokens)
{
    return std::ranges::any_of(line_tokens, [](const auto& i)
    {
        return i == TokenType::structe_datatype;
    });
}

static constexpr uint8_t SIZE_ARRAY_DATA_TYPE = 3;
static const TokenType TYPE_DATA_ARRAY[SIZE_ARRAY_DATA_TYPE]
{
    TokenType::number_datatype,
    TokenType::string_datatype,
    TokenType::character_datatype,
};

[[nodiscard]] static constexpr bool is_test_func_test(
    const std::vector<std::shared_ptr<IToken>>& line_tokens)
{
    return std::ranges::any_of(TYPE_DATA_ARRAY, [&line_tokens](const auto& i)
    {
        return std::ranges::any_of(line_tokens, [i](const auto& j)
        {
            return j == i;
        });
    });
}

[[nodiscard]] static constexpr uint32_t find_test_func(
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
            std::wstring name = line_tokens[find_test_func(line_tokens,
                    TokenType::id)]->getValue();
            std::wstring type = line_tokens[find_test_func(line_tokens,
                    TokenType::colon) + 1]->getValue();
            uint32_t line = line_tokens.front()->getLine();

            if (is_test_func_struct(line_tokens))
            {
                uint32_t index_braket_left = 
                    find_test_func(line_tokens, TokenType::left_bracket);
                uint32_t index_braket_right = 
                    find_test_func(line_tokens, TokenType::right_bracket);
                
                std::vector<std::shared_ptr<IToken>> temp;
                for (int j = index_braket_left + 1; j < index_braket_right - 1; j++)
                {
                    temp.push_back(line_tokens[j]);
                }

                _nodes.push_back(std::make_shared<Struct>(name, temp, type, line));
            }

            else if (is_test_func_test(line_tokens))
            {                
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

static constexpr uint8_t SIZE_ARRAY_LITERALS = 3;
static const TokenType ARRAY_LITERALS[SIZE_ARRAY_LITERALS]
{
    TokenType::number_literal,
    TokenType::string_literal,
    TokenType::character_literal,
};

void Parser::check_tokens(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    uint32_t position_err = 0;
    for (int i = 0; i < SIZE_ARRAY_DATA_TYPE; i++)
    {
        if (test_is_func(find_test_func(tokens, ARRAY_LITERALS[i]), 
            tokens, position_err, TYPE_DATA_ARRAY[i]))
        {
            std::wcout << "err: " << position_err << '\n';
            exit(EXIT_FAILURE);
        }
    }
}

Test_array Parser::get_test_func_structe(const std::wstring& key) const
{
    for (const auto& i : _nodes)
        if (i->get_name() == key && i->get_type_token() == L"структура")
            return std::any_cast<std::vector<std::shared_ptr<Node>>>(
                i->get_value());
    return {};
}

