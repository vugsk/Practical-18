

#include <iostream>

#include <Lexer.hpp>

using namespace std;
using namespace lexer;

// текстовый формат называется CPPON -> C++ Object Notation

// TEST -> tests/test.cpp
//      дописать основной cmake файл для работы с тестоми
//      и создать cmake файл для работы с тестами
//      и написать тесты на class Lexer
//      и на функции Config.hpp(может быть функции переедут в другое место)
//
// Parser.hpp
//      написать парсер который будет из вектора делать чуда
//
// Exception.hpp
//      написать оброботчик ошибок
//
// после проделанной работы можно приступать к работе над заданием
//
// WorkFile.hpp
//      переделать на использование wstring
//
// переписать, то что осталось и продолжить идти по под задачам
//
// предположительно мне нужно часов 24-48 в днях где-то 3-10 дней





int main()
{
    setlocale(LC_CTYPE, "");

    wstring filename = L"номер: число = 90;\nбуква: символ = \'ш\';"
            + wstring(L"\nтекст: строка = \"какой-то текст\";\n");

    std::wcout << L"Код:\n" << filename << '\n';

    for (Lexer l(filename); const auto& i : l.test_func())
            std::wcout << i->getToken() << ' ' << i->getValue() << std::endl;

    return 0;
}
