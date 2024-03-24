
#ifndef PARSER_HPP
#define PARSER_HPP

// #define PARSER_DEBUG

#ifdef PARSER_DEBUG
    #include <iostream>
#endif

#include <memory>
#include <set>
#include <vector>


class IToken;

class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    void parse(const std::vector<std::shared_ptr<IToken>>& tokens);

    #ifdef PARSER_DEBUG
        void printDebug() {}
    #endif

protected:
    bool is_test_func_struct();
    bool is_test_func_number();
    bool is_test_func_string();
    bool is_test_func_char();

private:
    std::set<std::vector<std::shared_ptr<IToken>>> _tokens_set;

};


#endif //PARSER_HPP
