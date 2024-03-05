
#include <iostream>


#include <IToken.hpp>
// #include <Lexer.hpp>
// #include <ILexer.hpp>
#include <Config.hpp>

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
    for(auto position = 0; position < input.size(); position++)
    {
        if (isQuote(input[position]))
            tokens.push_back(Factory_func(string_literal,
                test_st(input, position,
                    test_bind(input[position++], false))));

        if(IsDigit(input[position]))
            tokens.push_back(Factory_func(number_literal,
                test_st(input, position, IsDigit)));

        if (IsSymbol(input[position]))
        {
            wstring sb = test_st(input, position, IsLetterOrDigit);
            if (test_func_(TYPE_DATA_, test_func_auto(sb)).first)
                tokens.push_back(test_func_(TYPE_DATA_, test_func_auto(sb)).second);
            else
                tokens.push_back(Factory_func(id, sb));
        }

        if (test_func_(TYPE_CHAR_, test_bind(input[position], true)).first)
            tokens.push_back(test_func_(TYPE_CHAR_,
                test_bind(input[position], true)).second);

    }

    tokens.push_back(make_shared<Token>(TokenType::end, END));
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
