
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
    explicit Lexer(const wstring& input): m_input(input) {}

    std::vector<std::shared_ptr<IToken>> test_func()
    {
        for(auto pos = 0; pos < m_input.size(); pos++)
        {
            for (auto i : test_vec)
            {
                const shared_ptr<IToken> io = i(pos);
                if (test_if_null_token(io, NOTHING))
                    m_tokens.push_back(io);
            }
        }

        m_tokens.push_back(test_func_end());
        return m_tokens;
    }

protected:
    auto test_func_bind(const int pos, const bool is) const
    {
        return test_bind(m_input[pos], is);
    }

    shared_ptr<IToken> command_operator(const int pos)
    {
        if (test_func_check_class_token(test_func_(TYPE_CHAR_, test_func_bind(pos, true))))
            return test_func_(TYPE_CHAR_, test_func_bind(pos, true));
        return test_func_null(NOTHING);
    }

    shared_ptr<IToken> command_number(int& pos)
    {
        if (IsDigit(m_input[pos]))
            return test_func_number_leteral(test_st(m_input, pos, IsDigit));
        return test_func_null(NOTHING);
    }

    shared_ptr<IToken> command_string(int& pos)
    {
        if (isQuote(m_input[pos]))
            return test_func_string_leteral(test_st(m_input, pos,
                test_func_bind(pos++, false)));
        return test_func_null(NOTHING);
    }

    shared_ptr<IToken> command_command(int& pos)
    {
        if (IsSymbol(m_input[pos]))
        {
            const wstring sb = test_st(m_input, pos, IsLetterOrDigit);
            if (test_func_check_class_token(test_func_(TYPE_DATA_, test_func_auto(sb))))
                return test_func_(TYPE_DATA_, test_func_auto(sb));
            return test_func_id(sb);
        }
        return test_func_null(NOTHING);
    }



    void add(const function<shared_ptr<IToken>(int)>& func)
    {
        test_vec.push_back(func);
    }

    void remove()
    {
        if (test_vec.size() == MIN_SIZE_VEC)
            return;

        test_vec.pop_back();
    }

private:
    static const std::wstring NOTHING;
    static const size_t       MIN_SIZE_VEC;

    std::vector<std::shared_ptr<IToken>> m_tokens;
    wstring m_input;

    vector<function<shared_ptr<IToken>(int&)>> test_vec
    {
        [this](int& pos) {return command_command(pos);},
        [this](int& pos) {return command_number(pos);},
        [this](int& pos) {return command_string(pos);},
        [this](const int pos) {return command_operator(pos);},
    };
};

const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;




int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90;\nбуква: символ = \'ш\';\nтекст: строка = \"какой-то текст\";\n";

    std::wcout << L"Код:\n" << filename << '\n';

    for (Lexer l(filename); const auto& i : l.test_func())
            std::wcout << i->getToken() << ' ' << i->getValue() << std::endl;

    return 0;
}
