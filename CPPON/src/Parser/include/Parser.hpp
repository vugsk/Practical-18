
#ifndef PARSER_HPP
#define PARSER_HPP

// #define PARSER_DEBUG

#include <any>
#include <string>
#include <vector>

#ifdef PARSER_DEBUG
    #include <iostream>
#endif

#include <memory>

#include "Node.hpp"
#include "IToken.hpp"

class Test_str {
public:
    explicit Test_str(const std::vector<std::shared_ptr<Node>>& nodes)
        : _nodes(nodes) {}
    Test_str() {}
    
    std::any operator[](const std::wstring& key) {
        for (const auto& i : _nodes) {
            if (key == i->get_name()) {
                return i->get_value();
            }
        }
        return {};
    }
private:
    std::vector<std::shared_ptr<Node>> _nodes;

};

class Parser
{
public:
    explicit Parser(const std::vector<std::shared_ptr<IToken>>& tokens);

    Parser(const Parser& other)                = delete;
    Parser(Parser&& other) noexcept            = delete;
    Parser& operator=(const Parser& other)     = delete;
    Parser& operator=(Parser&& other) noexcept = delete;
    ~Parser()                                  = default;

    template<typename T>
    constexpr T get_test_func(const std::wstring& key) const
    {
        for (const auto& i : _nodes)
        {
            if (i->get_name() == key &&
                i->get_type_token() != L"структура")
            {
                return std::any_cast<T>(i->get_value());
            }
        }
        return T{};
    }

    Test_str get_test_func_structe(
        const std::wstring& key) const
    {
        for (const auto& i : _nodes)
        {
            if (i->get_name() == key &&
                i->get_type_token() == L"структура")
            {
                return Test_str(std::any_cast<std::vector<std::shared_ptr<Node>>>(i->get_value()));
            }
        }
        return Test_str();
    }

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

private:
    static const std::vector<std::vector<TokenType>> _test_funcs;
    std::vector<std::shared_ptr<Node>>               _nodes;
};


#endif //PARSER_HPP
