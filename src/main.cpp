
#include <iostream>


#include <Config.hpp>
#include <IToken.hpp>

using namespace std;

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
// WorkFile.hpp
//      переделать на использование wstring
//
// переписать, то что осталось и продолжить идти по под задачам
//
// предположительно мне нужно часов 24-48 в днях где-то 3-10 дней



std::vector<std::shared_ptr<IToken>> test_func(const wstring& input)
{
    std::vector<std::shared_ptr<IToken>> tokens;

    for(auto pos = 0; pos < input.size(); pos++)
    {
        if (isQuote(input[pos]))
            tokens.push_back(test_func_string_leteral(test_st(input, pos,
                test_bind(input[pos++], false))));

        if (IsDigit(input[pos]))
            tokens.push_back(test_func_number_leteral(
                test_st(input, pos, IsDigit)));

        if (IsSymbol(input[pos]))
        {
            const wstring sb = test_st(input, pos, IsLetterOrDigit);
            if (test_func_(TYPE_DATA_, test_func_auto(sb)).first)
                tokens.push_back(test_func_(TYPE_DATA_, test_func_auto(sb)).second);
            tokens.push_back(test_func_id(sb));
        }

        if (test_func_(TYPE_CHAR_, test_bind(input[pos], true)).first)
            tokens.push_back(test_func_(TYPE_CHAR_, test_bind(input[pos], true)).second);
    }

    tokens.push_back(test_func_end());
    return tokens;
}





int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90;\nбуква: символ = \'ш\';\nтекст: строка = \"какой-то текст\";\n";

    std::wcout << L"Код:\n" << filename << std::endl;

    for (const auto& i : test_func(filename))
            std::wcout << static_cast<int>(i->getToken()) << ' '
                        << i->getValue() << std::endl;

    return 0;
}
