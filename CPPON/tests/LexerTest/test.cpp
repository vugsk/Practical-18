
#include <gtest/gtest.h>

#include "Config.hpp"

#include "Lexer.hpp"

void TestOfOperatorsInToken(const std::shared_ptr<IToken>& token)
{
    for (const auto& [fst, snd] : OPERATORS)
        if (fst == token->getToken())
            EXPECT_EQ(token->getValue()[0], snd);
}

void TestingDataTypesInToken(const std::shared_ptr<IToken>& token)
{
    for (const auto& [fst, snd] : DATA_TYPES)
        if (fst == token->getToken())
            EXPECT_EQ(token->getValue(), snd);
}

void ForEachTokenApplyFunction(const std::wstring& test_code,
    const std::function<void(const std::shared_ptr<IToken>&)>& func)
{
    for (Lexer kl(test_code); const auto& j
        : kl.lexicalCodeAnalysis())
    {
        func(j);
    }
}

void TestTokensWithCustomFunction(
    const std::function<void(const std::shared_ptr<IToken>&)>& func)
{
    for (const auto& i : TEST_CODES)
        ForEachTokenApplyFunction(i, func);
}


TEST(TestPrint, Operators)
{
    TestTokensWithCustomFunction(TestOfOperatorsInToken);
}

TEST(TestPrint, TypeData)
{
    TestTokensWithCustomFunction(TestingDataTypesInToken);
}

TEST(TestFunctionIsQuote, Quote)
{
    EXPECT_TRUE(IsQuote('\''));
    EXPECT_TRUE(IsQuote('\"'));
}