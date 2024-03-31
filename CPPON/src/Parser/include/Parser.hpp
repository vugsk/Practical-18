
#ifndef PARSER_HPP
#define PARSER_HPP

// #define PARSER_DEBUG

#ifdef PARSER_DEBUG
    #include <iostream>
#endif

#include <memory>
#include <vector>

#include "Node.hpp"
#include "Token.hpp"

class Parser
{
public:
    explicit Parser(const std::vector<std::shared_ptr<IToken>>& tokens);

    Parser(const Parser& other)                = delete;
    Parser(Parser&& other) noexcept            = delete;
    Parser& operator=(const Parser& other)     = delete;
    Parser& operator=(Parser&& other) noexcept = delete;
    ~Parser()                                  = default;

    // template <typename T>
    // constexpr T get_test_func(const std::wstring& key) const
    // {
    //     return std::any_cast<T>(test_func_lol(key));
    // }

    #ifdef PARSER_DEBUG
        void printDebug() const
        {
            for (const auto& node : _nodes)
            {
                std::wcout << node->get_name() << ' '
                            << node->get_type_token() << ' '
                            << node->get_type_factic() << ' '
                            << node->get_line() << ' '
                            << node->get_value().type().name() << '\n';
            }
        }
    #endif

protected:
    constexpr void parse(const std::vector<std::shared_ptr<IToken>>& tokens);
    void check_tokens(const std::vector<std::shared_ptr<IToken>>& tokens);

    // std::any test_func_lol(const std::wstring& key) const;

private:
    static const std::vector<std::vector<TokenType>> _test_funcs;

    bool test_func_is_num(uint32_t index,
        const std::vector<std::shared_ptr<IToken>>& tokens);

    std::vector<std::shared_ptr<Node>>               _nodes;
};


#endif //PARSER_HPP
