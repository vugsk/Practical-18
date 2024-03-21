
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

vector<wstring> arr;

const wstring TEST_ = L"IN_STRING";
const wstring TEST_D = L"DEFAULT";

wstring       state               = TEST_D;
int           current_token_index = 0;
size_t current_line = 1;
size_t current_pos = 0;

wstring add_arr(const wstring& current_lexeme)
{
    arr.push_back(current_lexeme);
    ++current_token_index;
    return L"";
}

[[nodiscard]] static bool is_q(const wchar_t ch)
{
    return ch == '\"';
}

[[nodiscard]] static bool Is_quote(const wchar_t ch)
{
    return is_q(ch) || ch == '\'';
}

void func_string_literal(const wchar_t symbol, wstring& current_lexeme)
{
    if (Is_quote(symbol))
    {
        if (state == TEST_D)
            state = TEST_;
        else if (state == TEST_)
        {
            state = TEST_D;
            add_arr(current_lexeme);
            current_lexeme.clear();
        }
    }
}

[[nodiscard]] static bool is_space(const wchar_t ch)
{
    return ch == ' ';
}

[[nodiscard]] static bool is_enter(const wchar_t ch)
{
    return ch == '\n';
}

[[nodiscard]] static bool is_func_test_separators(const wchar_t ch)
{
    return !is_space(ch) && ch != '\r' && !is_enter(ch);
}

wstring test_func_if(const bool is, const wstring& current_lexeme)
{
    return is ? add_arr(current_lexeme) : L"";
}

static bool is_separate_symbol(const wchar_t symbol)
{
    return  symbol == ':'   || symbol == ';' ||
            symbol == ','   || symbol == '(' ||
            symbol == ')'   || symbol == '[' ||
            symbol == ']'   || symbol == '=' ||
            is_space(symbol)|| symbol == '\r'||
            is_enter(symbol)|| symbol == '#';
}

void test_func_str(const wchar_t symbol, wstring& current_lexeme)
{
    if (is_separate_symbol(symbol))
    {
        current_lexeme = test_func_if(!current_lexeme.empty(), current_lexeme);
        test_func_if(is_func_test_separators(symbol),
            wstring(1, symbol));
    }
    else
        current_lexeme += symbol;
}

template<typename T>
T test_func_T(const int& to, const int& from,
    const function<bool(const wstring&)>& func)
{
    for (auto i = to; i < from; ++i)
        if (func(arr[i]))
            return i;
    return 0;
}

[[nodiscard]] static bool is_front_str(const wstring& str)
{
    return is_q(str.front());
}

[[nodiscard]] static bool is_back_str(const wstring& str)
{
    return is_q(str.back());
}

wstring test_func_merge(const int index_to, const int index_from)
{
    if (is_space(arr[index_from].front()))
        return arr[index_to] + arr[index_from];
    return arr[index_to] + L" " + arr[index_from];
}

void test_func_m()
{
    auto index_start = test_func_T<int>(0, arr.size(), is_front_str),
         index_finish = test_func_T<int>(0, arr.size(), is_back_str);

    arr.insert(arr.begin() + index_start,
        test_func_merge(index_start, index_finish));

    erase_if(arr, [index_start, index_finish](const wstring& str)
    {
        return test_func_T<bool>(index_start + 1, index_finish + 2,
            [str](const wstring& string) { return string == str; });
    });
}

void test_func_main(const wstring& code)
{
    current_token_index = -1;
    wstring current_lexeme;
    for (const auto& symbol : code)
    {
        if (is_enter(symbol))
        {
            ++current_line;
            current_pos = 0;
        }

        test_func_str(symbol, current_lexeme);
        func_string_literal(symbol, current_lexeme);
    }
}

int main()
{
    setlocale(LC_CTYPE, "");

    string filenam_test = "File_program_code";
    string filename_release = "db_students.txt";

    const wstring text_code(read_file_test(filenam_test));
    test_func_main(text_code);
    test_func_m();

    wcout << '\n';
    for (const auto& i : arr)
        wcout << i << '\n';

    return 0;
}

