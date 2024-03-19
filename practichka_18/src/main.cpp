
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

bool Is_test(const wchar_t ch)
{
    return ch == L':' || ch == L';' || ch == L'=';
}

bool Is_quote(const wchar_t ch)
{
    return ch == L'\'' || ch == L'\"';
}

bool Is_space(const wchar_t ch)
{
    return ch != L' ';
}

wstring test_func_test(const wstring& text, const function<bool(wchar_t)>& func)
{
    wstring test;
    for (auto it = text.begin(), end = text.end(); (it != end) && func(*it); ++it)
        test.push_back(*it);
    return test;
}

wstring test_tstt(const wstring& str, wstring& text)
{
    text.erase(0, str.length());
    return str;
}


int main()
{
    setlocale(LC_CTYPE, "");

    vector<wstring> arr;

    vector<function<bool(wchar_t)>> func_test
    {
        /*iswalpha, Is_test, Is_quote, iswdigit,*/Is_space, iswprint
    };

    ifstream file("File_program_code");

    if (!file.is_open())
    {
        puts("ERROR: NOT OPEN FILE");
        exit(EXIT_FAILURE);
    }

    std::string str;
    while (std::getline(file, str))
    {
        wstring wstr = ConvertString(str);

        for (auto j : wstr)
            for (auto i : func_test)
                arr.push_back(test_tstt(test_func_test(wstr, i), wstr));
    }

    file.close();

    for (const auto& i : arr)
        if (!i.empty()) wcout << i << '\n';

    // std::wcout << L"Код:\n" << filename << '\n';
    // Lexer l(filename);
    // wcout << L"Обработка лексера:\n";
    // for (const auto& i : l.lexicalCodeAnalysis())
    //     std::wcout << i->getToken().tokenType << ' ' << i->getToken().value
    //                 << " | " << i->getValue() << '\n';



    return 0;
}

