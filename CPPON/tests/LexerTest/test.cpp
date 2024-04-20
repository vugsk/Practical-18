
#include <gtest/gtest.h>

#define TEST_LEXER
#include "ConfigTest.hpp"
#include "Lexer.hpp"


TEST(TestLexer, SeparatorOnWords)
{
    Lexer l;
    for (const auto& [test_str, answers_str]
        : TEST_CODES)
    {
        l.parseForTest(test_str);
        ASSERT_TRUE(!l.getWords().empty()) << "array empty";
        ASSERT_EQ(l.getWords().size(), answers_str.size());
        for (auto i = 0; i < l.getWords().size(); i++)
            EXPECT_EQ(l.getWords()[i].first, answers_str[i]);
    }
}

TEST(TestLexer, Token)
{
    for (const auto& [test_str, answers_str]
        : TESTS_TOKENS_ANSWERS)
    {
        ASSERT_EQ(test_str.size(), answers_str.size()) << "size mismatch";
        for (auto i = 0; i < test_str.size(); i++)
        {
            Token token(test_str[i]);
            EXPECT_EQ(token.getToken(), answers_str[i]);
        }
    }
}
