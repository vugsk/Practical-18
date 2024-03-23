
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "Token.hpp"

template<typename T>
constexpr std::vector<T> VectorAddition(const std::vector<T>& vec1,
    const std::vector<T>& vec2)
{
    std::vector<T> temp;
    for (auto i : vec1)
        temp.push_back(i);
    for (auto i : vec2)
        temp.push_back(i);
    return temp;
}

const std::wstring TEST_CODE_1 = L"текст: \nстрока = \"лдва\";";
const std::wstring TEST_CODE_2 = L"тghк: символ = \n'Д';";
const std::wstring TEST_CODE_3 = L"РОЛ\n: число=0;";
const std::wstring TEST_CODE_4 = L"dklf:число\n=89990;";

const std::vector<std::wstring> TEST_CODE_1_ANSWERS
{
    L"текст", L":", L"строка", L"=", L"\"лдва\"", L";"
};

const std::vector<std::wstring> TEST_CODE_2_ANSWERS
{
    L"тghк", L":", L"символ", L"=", L"'Д'", L";"
};

const std::vector<std::wstring> TEST_CODE_3_ANSWERS
{
    L"РОЛ", L":", L"число", L"=", L"0", L";"
};

const std::vector<std::wstring> TEST_CODE_4_ANSWERS
{
    L"dklf", L":", L"число", L"=", L"89990", L";"
};

const std::vector TEST_TOKEN_1_ANSWERS
{
    TokenType::id, TokenType::colon,
    TokenType::string_datatype, TokenType::assignment,
    TokenType::string_literal, TokenType::semicolon
};

const std::vector TEST_TOKEN_2_ANSWERS
{
    TokenType::id, TokenType::colon,
    TokenType::character_datatype, TokenType::assignment,
    TokenType::character_literal, TokenType::semicolon
};

const std::vector TEST_TOKEN_3_ANSWERS
{
    TokenType::id, TokenType::colon,
    TokenType::number_datatype, TokenType::assignment,
    TokenType::number_literal, TokenType::semicolon
};

const std::vector TEST_TOKEN_4_ANSWERS
{
    TokenType::id, TokenType::colon,
    TokenType::number_datatype, TokenType::assignment,
    TokenType::number_literal, TokenType::semicolon
};

const std::wstring TEST_CODE_5 = TEST_CODE_1 + TEST_CODE_4;
const std::wstring TEST_CODE_6 = TEST_CODE_5 + TEST_CODE_2;
const std::wstring TEST_CODE_7 = TEST_CODE_3 + TEST_CODE_6;
const std::wstring TEST_CODE_8 = TEST_CODE_7 + TEST_CODE_1;

const std::vector TEST_CODE_5_ANSWERS = VectorAddition(TEST_CODE_1_ANSWERS,
                                                        TEST_CODE_4_ANSWERS);
const std::vector TEST_CODE_6_ANSWERS = VectorAddition(TEST_CODE_5_ANSWERS,
                                                        TEST_CODE_2_ANSWERS);
const std::vector TEST_CODE_7_ANSWERS = VectorAddition(TEST_CODE_3_ANSWERS,
                                                        TEST_CODE_6_ANSWERS);
const std::vector TEST_CODE_8_ANSWERS = VectorAddition(TEST_CODE_7_ANSWERS,
                                                        TEST_CODE_1_ANSWERS);

const std::vector TEST_TOKEN_5_ANSWERS = VectorAddition(TEST_TOKEN_1_ANSWERS,
                                                        TEST_TOKEN_4_ANSWERS);
const std::vector TEST_TOKEN_6_ANSWERS = VectorAddition(TEST_TOKEN_5_ANSWERS,
                                                        TEST_TOKEN_2_ANSWERS);
const std::vector TEST_TOKEN_7_ANSWERS = VectorAddition(TEST_TOKEN_3_ANSWERS,
                                                        TEST_TOKEN_6_ANSWERS);
const std::vector TEST_TOKEN_8_ANSWERS = VectorAddition(TEST_TOKEN_7_ANSWERS,
                                                        TEST_TOKEN_1_ANSWERS);

const std::vector<std::pair<std::wstring, std::vector<std::wstring>>> TEST_CODES
{
    {TEST_CODE_1, TEST_CODE_1_ANSWERS},
    {TEST_CODE_2, TEST_CODE_2_ANSWERS},
    {TEST_CODE_3, TEST_CODE_3_ANSWERS},
    {TEST_CODE_4, TEST_CODE_4_ANSWERS},
    {TEST_CODE_5, TEST_CODE_5_ANSWERS},
    {TEST_CODE_6, TEST_CODE_6_ANSWERS},
    {TEST_CODE_7, TEST_CODE_7_ANSWERS},
    {TEST_CODE_8, TEST_CODE_8_ANSWERS},
};

const std::vector<std::pair<std::vector<std::wstring>,
    std::vector<TokenType>>> TESTS_TOKENS_ANSWERS
{
    {TEST_CODE_1_ANSWERS, TEST_TOKEN_1_ANSWERS},
    {TEST_CODE_2_ANSWERS, TEST_TOKEN_2_ANSWERS},
    {TEST_CODE_3_ANSWERS, TEST_TOKEN_3_ANSWERS},
    {TEST_CODE_4_ANSWERS, TEST_TOKEN_4_ANSWERS},
    {TEST_CODE_5_ANSWERS, TEST_TOKEN_5_ANSWERS},
    {TEST_CODE_6_ANSWERS, TEST_TOKEN_6_ANSWERS},
    {TEST_CODE_7_ANSWERS, TEST_TOKEN_7_ANSWERS},
    {TEST_CODE_8_ANSWERS, TEST_TOKEN_8_ANSWERS},
};


#endif //CONFIG_HPP
