
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


class Lexer
{
public:
    std::vector<std::shared_ptr<IToken>> test_func(const wstring& input)
    {
        for(auto pos = 0; pos < input.size(); pos++)
            test_func_for(input, pos);
        m_tokens.push_back(test_func_end());
        return m_tokens;
    }
protected:
    void test_func_for(const wstring& input, int& pos)
    {
        for (auto i : test_vec)
            m_tokens.push_back(i(input, pos));
    }


    shared_ptr<IToken> command_operator(const wstring& input, int pos)
    {
        if (test_func_check_class_token(test_func_(TYPE_CHAR_, test_bind(input[pos], true))))
            return test_func_(TYPE_CHAR_, test_bind(input[pos], true));
        return test_func_null();
    }

    shared_ptr<IToken> command_number(const wstring& input, int& pos)
    {
        if (IsDigit(input[pos]))
            return test_func_number_leteral(
                test_st(input, pos, IsDigit));
        return test_func_null();
    }

    shared_ptr<IToken> command_string(const wstring& input, int& pos)
    {
        if (isQuote(input[pos]))
            return test_func_string_leteral(test_st(input, pos,
                test_bind(input[pos++], false)));
        return test_func_null();
    }

    shared_ptr<IToken> command_command(const wstring& input, int& pos)
    {
        if (IsSymbol(input[pos]))
        {
            const wstring sb = test_st(input, pos, IsLetterOrDigit);
            if (test_func_check_class_token(test_func_(TYPE_DATA_, test_func_auto(sb))))
                return test_func_(TYPE_DATA_, test_func_auto(sb));
            return test_func_id(sb);
        }
        return test_func_null();
    }

private:
    std::vector<std::shared_ptr<IToken>> m_tokens;
    vector<function<shared_ptr<IToken>(const wstring&, int&)>> test_vec
    {
        [this](const wstring& t, int& pos) {return command_command(t, pos);},
        [this](const wstring& t, int& pos) {return command_number(t, pos);},
        [this](const wstring& t, int& pos) {return command_string(t, pos);},
        [this](const wstring& t, const int pos) {return command_operator(t, pos);},
    };
};




int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90;\nбуква: символ = \'ш\';\nтекст: строка = \"какой-то текст\";\n";

    std::wcout << L"Код:\n" << filename << '\n';

    for (Lexer l; const auto& i : l.test_func(filename))
            std::wcout << i->getToken() << ' ' << i->getValue() << std::endl;

    return 0;
}
