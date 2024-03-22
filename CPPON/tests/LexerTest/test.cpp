
#include <gtest/gtest.h>

#include "ConfigTest.hpp"

#define TEST_LEXER
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
        for (int i = 0; i < l.getWords().size(); i++)
            EXPECT_EQ(l.getWords()[i], answers_str[i]);
    }
}


