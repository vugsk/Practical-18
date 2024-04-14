
#ifndef PARSER_HPP
#define PARSER_HPP

// #define PARSER_DEBUG

#include <any>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#ifdef PARSER_DEBUG
    #include <iostream>
#endif

#include "Node.hpp"
#include "IToken.hpp"

class Test_array
{
public:
    Test_array() {}
    Test_array(const std::vector<std::shared_ptr<Node>>& list)
    {
        _arr = list;
    }
    Test_array(const Test_array& other)
    {
        _arr = other._arr;
    }

    template<typename T1>
    T1 getVal(const std::wstring& key)
    {
        for (auto i : _arr)
            if (i->get_name() == key)
                return std::any_cast<T1>(i->get_value());
        return T1{};
    }

private:
    std::vector<std::shared_ptr<Node>> _arr;
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

    uint32_t getSize()
    {
        int count = 0;
        for (const auto& i : _nodes)
            if (i->get_type_token() == L"структура")
                count++;
        return count;
    }

    Test_array get_test_func_structe(const std::wstring& key) const;

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
