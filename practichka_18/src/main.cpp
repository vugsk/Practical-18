
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

wstring add_arr(const wstring& current_lexeme)
{
    arr.push_back(current_lexeme);
    ++current_token_index;
    return L"";
}

[[nodiscard]] static bool Is_quote(const wchar_t ch)
{
    return ch == '\"' || ch == '\'';
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

[[nodiscard]] static bool is_func_test_separators(const wchar_t ch)
{
    return ch != ' ' && ch != '\r' && ch != '\n';
}

wstring test_func_if(const bool is, const wstring& current_lexeme)
{
    return is ? add_arr(current_lexeme) : L"";
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


int main()
{
    setlocale(LC_CTYPE, "");

    string filenam_test = "File_program_code";
    string filename_release = "db_students.txt";

    wstring text_code(read_file_test(filenam_test));

    current_token_index = -1;
    wstring current_lexeme;

    for (const auto& symbol : text_code)
    {
        if (symbol == '\n')
        {
            ++current_line;
            current_pos = 0;
        }

        test_func_str(symbol, current_lexeme);
        func_string_literal(symbol, current_lexeme);

    }

    bool start       = false;
    bool finih       = false;
    int  index_start = 0;
    int  index_finish = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].front() == '\"')
        {
            index_start = i;
            start = true;
        }

        if (start && arr[i].back() == '\"')
        {
            index_finish = i;
            finih = true;
        }
    }

    wcout << "start: " << start
          << " finish: " << finih
          << " index start: " << index_start
          << " index finish: " << index_finish << '\n';
    wcout << "text start index: " << arr[index_start]
            << "\ntext finish index: " << arr[index_finish] << '\n';

    if (start != finih)
        wcout << "ERROR: quote";

    if (index_start != index_finish)
    {
        wstring text;
        if (arr[index_finish].front() == ' ')
            text = arr[index_start] + arr[index_finish];
        else
            text = arr[index_start] + L" " + arr[index_finish];

        erase_if(arr, [](const wstring& str)
        {
            return str.front() == '\"' || str.back() == '\"';
        });
        arr.insert(arr.begin()+index_start, text);
    }

    wcout << '\n';
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

