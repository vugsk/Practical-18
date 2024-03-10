
#include <gtest/gtest.h>

#include "Config.hpp"

#include "Lexer.hpp"

void test_func_t(const std::shared_ptr<IToken>& token)
{
    for (const auto& [fst, snd] : OPERATORS)
        if (fst == token->getToken())
            EXPECT_EQ(token->getValue()[0], snd);
}

void test_func_f(const std::shared_ptr<IToken>& token)
{
    for (const auto& [fst, snd] : DATA_TYPES)
        if (fst == token->getToken())
            EXPECT_EQ(token->getValue(), snd);
}

void Test_func(const std::wstring& test_code,
    const std::function<void(const std::shared_ptr<IToken>&)>& func)
{
    for (Lexer kl(test_code); const auto& j
        : kl.lexicalCodeAnalysis())
    {
        func(j);
    }
}

void test_func_g(const std::function<void(const std::shared_ptr<IToken>&)>& func)
{
    for (auto i : TEST_CODES)
        Test_func(i, func);
}


TEST(TestPrint, Operators)
{
    test_func_g(test_func_t);
}

TEST(TestPrint, TypeData)
{
    test_func_g(test_func_f);
}

TEST(TestFunctionIsQuote, Quote)
{
    EXPECT_TRUE(IsQuote('\''));
    EXPECT_TRUE(IsQuote('\"'));
}