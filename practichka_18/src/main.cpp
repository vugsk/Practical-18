
#include <fstream>
#include <iostream>

#include "Config.hpp"


#define DEBUG_LEXER
#include "Lexer.hpp"

#define DEBUG_TOKEN
#include "Token.hpp"

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

int main()
{
    setlocale(LC_CTYPE, "");

    const string filenam_test = "File_program_code";
    const string filename_release = "db_students.txt";

    const wstring text_code(read_file_test(filenam_test));
    wcout << text_code << '\n';
    Lexer l(text_code);

    for (const auto& i : Lexer::test_func())
        wcout << static_cast<int>(i->getToken()) << ' ' << i->getValue() << '\n';

    return 0;
}

