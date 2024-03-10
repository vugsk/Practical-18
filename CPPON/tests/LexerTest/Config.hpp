
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

const std::wstring TEST_CODE_1 = L"текст: \nстрока = \"лдва\";";
const std::wstring TEST_CODE_2 = L"тАfdк: символ = \n'Д';";
const std::wstring TEST_CODE_3 = L"РОЛ\n: число=0;";
const std::wstring TEST_CODE_4 = L"dklf: число\n=89990;";

const std::wstring TEST_CODE_5 = TEST_CODE_1 + TEST_CODE_4;
const std::wstring TEST_CODE_6 = TEST_CODE_5 + TEST_CODE_2;
const std::wstring TEST_CODE_7 = TEST_CODE_3 + TEST_CODE_6;
const std::wstring TEST_CODE_8 = TEST_CODE_7 + TEST_CODE_1;

const std::vector TEST_CODES
{
    TEST_CODE_1,
    TEST_CODE_2,
    TEST_CODE_3,
    TEST_CODE_4,
    TEST_CODE_5,
    TEST_CODE_6,
    TEST_CODE_7,
    TEST_CODE_8,
};

#endif //CONFIG_HPP
