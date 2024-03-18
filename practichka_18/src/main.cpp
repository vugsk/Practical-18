
#include <iostream>

#include "Lexer.hpp"
#include "Parser.hpp"

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


int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename = L"номер: число = 90;\nбуква: символ = \'ш\';"
            + wstring(L"\nтекст: строка = \"какой-то текст\";\n");

    std::wcout << L"Код:\n" << filename << '\n';

    Lexer l(filename);
    Parser p;

    for (const auto& [fst, snd] : p.parse(l.lexicalCodeAnalysis()).root)
    {
        if (snd.first == L"число")
            wcout << fst << ' ' << snd.first << ' ' << get<int>(snd.second) << '\n';
        else if (snd.first == L"символ")
            wcout << fst << ' ' << snd.first << ' ' << get<wchar_t>(snd.second) << '\n';
        else if (snd.first == L"строка")
            wcout << fst << ' ' << snd.first << ' ' << get<wstring>(snd.second) << '\n';
    }

    //
    // wcout << "Обработка лексера:\n";
    // for (const auto& i : l.lexicalCodeAnalysis())
    //     std::wcout << i->getToken() << ' ' << i->getValue() << '\n';
    //
    // wcout << "\nРабота парсера\n";



    return 0;
}

