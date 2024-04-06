
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

    std::shared_ptr<Node> get_test_func(const std::wstring& key) const;

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

        std::vector<std::shared_ptr<Node>> get__() { return _nodes; }
    #endif

protected:
    constexpr void parse(const std::vector<std::shared_ptr<IToken>>& tokens);
    void check_tokens(const std::vector<std::shared_ptr<IToken>>& tokens);

private:
    static const std::vector<std::vector<TokenType>> _test_funcs;
    std::vector<std::shared_ptr<Node>>               _nodes;
};


#endif //PARSER_HPP
