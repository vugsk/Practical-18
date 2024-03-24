
#include "Parser.hpp"

#include "IToken.hpp"


void Parser::parse(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    std::vector<std::shared_ptr<IToken>> line_tokens;

    // for (const auto& i : tokens)
    // {
    //     if (i->getValue() == L";")
    //     {
    //         line_tokens.push_back(i);
    //         tokens_set.insert(line_tokens);
    //         line_tokens.clear();
    //         continue;
    //     }
    //     if (i->getValue() == L"END")
    //     {
    //         line_tokens.push_back(i);
    //         tokens_set.insert(line_tokens);
    //         line_tokens.clear();
    //         break;
    //     }
    //     line_tokens.push_back(i);
    // }

    for (uint32_t j = 1; j < tokens.back()->getLine() + 1; j++)
    {
        for (const auto& i : tokens)
            if (i->getLine() == j)
                line_tokens.push_back(i);

        _tokens_set.insert(line_tokens);
        line_tokens.clear();
    }
}

bool Parser::is_test_func_struct() { return true; }

bool Parser::is_test_func_number()
{

}

bool Parser::is_test_func_string()
{ return true; }

bool Parser::is_test_func_char()
{ return true; }
