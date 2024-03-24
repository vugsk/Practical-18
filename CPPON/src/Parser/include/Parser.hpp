
#ifndef PARSER_HPP
#define PARSER_HPP

// #define PARSER_DEBUG

#ifdef PARSER_DEBUG
    #include <iostream>
#endif

#include <memory>
#include <set>
#include <variant>
#include <vector>

#include "Token.hpp"

class Parser
{
public:
    explicit Parser(const std::vector<std::shared_ptr<IToken>>& tokens);
    ~Parser() = default;

     std::variant<int, wchar_t, std::wstring> test_func_lol(
        const std::wstring& key) const
    {
        for (auto i : _tokens_set)
        {
            if (i.front()->getValue() == key)
            {
                if (is_test_func_number(i))
                    return std::stoi(i[i.size() - 2]->getValue());
                if (is_test_func_string(i))
                    return i[i.size() - 2]->getValue();
                if (is_test_func_char(i))
                    return i[i.size() - 2]->getValue()[1];
            }
        }
        return 0;
    }

    #ifdef PARSER_DEBUG
        void printDebug() {}
    #endif

protected:
    void parse(const std::vector<std::shared_ptr<IToken>>& tokens);
    void check_tokens() const;

    bool        is_test_func_struct();
    static bool is_test_func_number(
        const std::vector<std::shared_ptr<IToken>>& line_tokens);
    static bool is_test_func_string(
        const std::vector<std::shared_ptr<IToken>>& line_tokens);
    static bool is_test_func_char(
        const std::vector<std::shared_ptr<IToken>>& line_tokens);

private:
    std::set<std::vector<std::shared_ptr<IToken>>> _tokens_set;

    static const std::vector<std::vector<TokenType>> _test_funcs;

};


#endif //PARSER_HPP
