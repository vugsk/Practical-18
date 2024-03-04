
#include <iostream>

#include <Lexer.hpp>

using namespace std;

// class Lexer -> Lexer.hpp
//    test_func() - упростить и тоже избавиться от class Token
//    test_func_() - переделать и избавиться от использования напримую class Token
//                   и ещё упростить и как-то избавиться от использования pair<>
//    identifierOrKeyword() - вследствии чего вот это функцию переделать
//                            и тоже избавиться от class Token
// main.cpp
//    сделать механизм чтобы можно была создавать объект Lexer не использую
//    напримую class Lexer только его интерфейс, тоже самое с class Token
//
// ConfigConcepts.hpp
//      написать несколько концептов для шаблонов
//
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
// WirkFile.hpp
//      переделать на использование wstring
//
// переписать, то что осталось и продолжить идти по под задачам
//
// предположительно мне нужно часов 24-48 в днях где-то 3-10 дней



int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90;\nбуква: символ = \'ш\';\nтекст: строка = \"какой-то текст\";\n";

    std::wcout << L"Код:\n" << filename << std::endl;

    for (Lexer l(filename); const auto& i : l.test_func())
        std::wcout << static_cast<int>(i->getToken()) << ' '
                    << i->getValue() << std::endl;

    return 0;
}
