
#include <iostream>


#include <Config.hpp>
#include <IToken.hpp>
#include <utility>

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
    explicit Lexer(wstring input): m_input(std::move(input)) {}

    std::vector<std::shared_ptr<IToken>> test_func()
    {
        for(auto pos = 0; pos < m_input.size(); pos++)
        {
            for (const auto& i : test_vec)
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
    function<bool(const wchar_t&)> test_func_bind(const int pos, const bool is) const
    {
        return test_bind(m_input[pos], is); // return function
    }

    std::wstring test_st(int& position, const std::function<bool(wchar_t)>& func) const
    {
        std::wstring sb;
        while (func(m_input[position]))
            sb.push_back(m_input[position++]);
        return sb;
    }

    template<typename F>
    shared_ptr<IToken> test_func_shared_ptr_num(int& pos, const TokenType token,
        const function<bool(wchar_t)>& func, const F& func1)
    {
        if (func(m_input[pos]))
            return test_func_factory(token, test_st(pos, func1(pos)));
        return test_func_null(NOTHING);
    }

    shared_ptr<IToken> command_operator(const int pos) const
    {
        return test_func_(TYPE_CHAR_, test_func_bind(pos, true),
            test_func_null(NOTHING));
    }

    shared_ptr<IToken> command_number(int& pos)
    {
        return test_func_shared_ptr_num(pos, number_literal, IsDigit,
            test_func_bind_lamda(IsDigit));
    }

    shared_ptr<IToken> command_string(int& pos)
    {
        return test_func_shared_ptr_num(pos, string_literal, isQuote,
            [this](int& i) { return test_func_bind(i++, false); });
    }

    shared_ptr<IToken> command_command(int& pos) const
    {
        if (IsSymbol(m_input[pos]))
            return test_func_(TYPE_DATA_, test_func_auto(test_st(pos, IsLetterOrDigit)), test_func_id(test_st(pos, IsLetterOrDigit)));
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

    const wstring filename = L"номер: число = 90;\nбуква: символ = \'ш\';"
            + wstring(L"\nтекст: строка = \"какой-то текст\";\n");

    std::wcout << L"Код:\n" << filename << '\n';

    for (Lexer l(filename); const auto& i : l.test_func())
            std::wcout << i->getToken() << ' ' << i->getValue() << std::endl;

    return 0;
}
