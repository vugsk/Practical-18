
#include <iostream>
#include <TypeToken.hpp>
#include <algorithm>
#include <Config.hpp>
#include <fstream>
#include <functional>

#include "Lexer.hpp"

using namespace std;



// *  текстовый формат называется CPPON -> C++ Object Notation

// [[Parser.hpp]]
// *      написать парсер который будет из вектора делать чуда

// ? [[Exception.hpp]]
// *      написать оброботчик ошибок

// * после проделанной работы можно приступать к работе над заданием

// [[WorkFile.hpp]]
// *      переделать на использование wstring

// * переписать, то что осталось и продолжить идти по под задачам

// * предположительно мне нужно часов 24-48 в днях где-то 3-10 дней


wstring read_file_test(const string& filename)
{
    ifstream file(filename, ios::binary);

    if (!file.is_open())
    {
        puts("ERROR: NOT OPEN FILE");
        exit(EXIT_FAILURE);
    }

    const long size = file.seekg(0, ios::end).tellg();
    file.seekg(0);

    string te;
    te.resize(size);
    file.read(&te[0], size);

    file.close();
    return ConvertString(te);
}

const wstring TEST_ = L"IN_STRING";
const wstring TEST_D = L"DEFAULT";

wstring       state               = TEST_D;
int           current_token_index = 0;

wstring test_if(bool is, const wstring& t)
{
    if (is)
        return t;
    return L"";
}

wstring test_if_x2(wchar_t symbol, const wstring& D, const wstring& _d)
{
    if (symbol == '"' && state == D)
    {
        state = _d;
        return wstring(1, symbol);
    }
    return L"";
}

wstring test_func(wchar_t symbol)
{
    return test_if((state == TEST_), wstring(1, symbol)).empty()
        ? !test_if_x2(symbol, TEST_, TEST_D).empty()
            ? test_if_x2(symbol, TEST_, TEST_D)
            : test_if_x2(symbol, TEST_D, TEST_)
        : test_if((state == TEST_), wstring(1, symbol));
}

int main()
{
    setlocale(LC_CTYPE, "");

    vector<wstring> arr;
    wstring text_code(read_file_test("File_program_code"));

    current_token_index = -1;
    size_t current_line = 1;
    size_t current_pos = 0;
    wstring current_lexeme;

    for (const auto& symbol : text_code)
    {
        if (symbol == '\n')
        {
            ++current_line;
            current_pos = 0;
        }

        current_lexeme += test_func(symbol);

    }

    wcout << current_lexeme;

    // for (const auto& i : arr)
    //     if (!i.empty()) wcout << i << '\n';

    // std::wcout << L"Код:\n" << filename << '\n';
    // Lexer l(filename);
    // wcout << L"Обработка лексера:\n";
    // for (const auto& i : l.lexicalCodeAnalysis())
    //     std::wcout << i->getToken().tokenType << ' ' << i->getToken().value
    //                 << " | " << i->getValue() << '\n';



    return 0;
}

