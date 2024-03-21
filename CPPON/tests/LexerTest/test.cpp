
#include <gtest/gtest.h>

#include "ConfigTest.hpp"

#define TEST_LEXER
#include <codecvt>

#include "Lexer.hpp"

std::string ConvertWstring(const std::wstring& string)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(string);
}

// ! fix problem
TEST(TestLexer, SeparatorOnWords)
{
    Lexer l;

    for (const auto& [test_str, answers_str]
        : TEST_CODES)
    {
        l.parseForTest(test_str);
        ASSERT_EQ(l.getWords().size(), answers_str.size());
        for (int i = 0; i < l.getWords().size(); i++)
            EXPECT_EQ(l.getWords()[i], answers_str[i]);
    }

}
