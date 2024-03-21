
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

static bool is_separate_symbol(const wchar_t symbol)
{
    return  symbol == ':' || symbol == ';' ||
            symbol == ',' || symbol == '(' ||
            symbol == ')' || symbol == '[' ||
            symbol == ']' || symbol == '=' ||
            symbol == ' ' || symbol == '\r'||
            symbol == '\n'|| symbol == '#';
}

vector<wstring> arr;

const wstring TEST_ = L"IN_STRING";
const wstring TEST_D = L"DEFAULT";

wstring       state               = TEST_D;
int           current_token_index = 0;
size_t current_line = 1;
size_t current_pos = 0;

void func_string_literal(wchar_t symbol, wstring& current_lexeme)
{
    if (symbol == '\"' || symbol == '\'')
    {
        if (state == TEST_D)
            state = TEST_;
        else if (state == TEST_)
        {
            state = TEST_D;
            arr.push_back(current_lexeme);
            ++current_token_index;
            current_lexeme.clear();
        }
    }
}

void test_func_data_type() {}

void test_func_if(bool is, wstring& current_lexeme, bool is2)
{
    if (is)
    {
        arr.push_back(current_lexeme);
        if (is2)
            current_lexeme.clear();
        ++current_token_index;
    }
}

void test_func_operator(wchar_t symbol, wstring& current_lexeme)
{
    if (is_separate_symbol(symbol))
    {
        test_func_if(!current_lexeme.empty(), current_lexeme, true);
        // if (!current_lexeme.empty())
        // {
        //     arr.push_back(current_lexeme);
        //     current_lexeme.clear();
        //     ++current_token_index;
        // }
        wstring op(1, symbol);
        test_func_if(symbol != ' ' && symbol != '\r' && symbol != '\n',
            op, false);
        // if (symbol != ' ' && symbol != '\r' && symbol != '\n')
        // {
        //     arr.push_back(wstring(1, symbol));
        //     ++current_token_index;
        // }
    }
    else
        current_lexeme += symbol;
}


int main()
{
    setlocale(LC_CTYPE, "");

    wstring text_code(read_file_test("File_program_code"));

    current_token_index = -1;
    wstring current_lexeme;

    for (const auto& symbol : text_code)
    {
        if (symbol == '\n')
        {
            ++current_line;
            current_pos = 0;
        }

        test_func_operator(symbol, current_lexeme);
        func_string_literal(symbol, current_lexeme);

    }


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

