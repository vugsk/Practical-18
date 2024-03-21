
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

inline std::vector<std::wstring> vectorAddition(
    const std::vector<std::wstring>& vec1, const std::vector<std::wstring>& vec2)
{
    std::vector<std::wstring> temp;
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
    L"тАfdк", L":", L"символ", L"=", L"'Д'", L";"
};

const std::vector<std::wstring> TEST_CODE_3_ANSWERS
{
    L"РОЛ", L":", L"число", L"=", L"0", L";"
};

const std::vector<std::wstring> TEST_CODE_4_ANSWERS
{
    L"dklf", L":", L"число", L"=", L"89990", L";"
};

const std::wstring TEST_CODE_5 = TEST_CODE_1 + TEST_CODE_4;
const std::wstring TEST_CODE_6 = TEST_CODE_5 + TEST_CODE_2;
const std::wstring TEST_CODE_7 = TEST_CODE_3 + TEST_CODE_6;
const std::wstring TEST_CODE_8 = TEST_CODE_7 + TEST_CODE_1;

const std::vector TEST_CODE_5_ANSWERS = vectorAddition(TEST_CODE_1_ANSWERS, TEST_CODE_4_ANSWERS);
const std::vector TEST_CODE_6_ANSWERS = vectorAddition(TEST_CODE_5_ANSWERS, TEST_CODE_2_ANSWERS);
const std::vector TEST_CODE_7_ANSWERS = vectorAddition(TEST_CODE_3_ANSWERS, TEST_CODE_6_ANSWERS);
const std::vector TEST_CODE_8_ANSWERS = vectorAddition(TEST_CODE_7_ANSWERS, TEST_CODE_1_ANSWERS);

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

#endif //CONFIG_HPP
