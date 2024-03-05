
#include <iostream>


#include <IToken.hpp>
// #include <Lexer.hpp>
// #include <ILexer.hpp>
#include <Config.hpp>

using namespace std;

//! class Lexer -> Lexer.hpp
//!    test_func() - упростить и тоже избавиться от class Token
//!    test_func_() - переделать и избавиться от использования напримую class Token
//!                   и ещё упростить и как-то избавиться от использования pair<>
//!    identifierOrKeyword() - вследствии чего вот это функцию переделать
//!                            и тоже избавиться от class Token
//! main.cpp
//!    сделать механизм чтобы можно была создавать объект Lexer не использую
//!    напримую class Lexer только его интерфейс, тоже самое с class Token
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
// WorkFile.hpp
//      переделать на использование wstring
//
// переписать, то что осталось и продолжить идти по под задачам
//
// предположительно мне нужно часов 24-48 в днях где-то 3-10 дней

class Lexer final
{
public:
    Lexer() = default;
    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer()                        = default;

    std::vector<std::shared_ptr<IToken>> test_func(const wstring& input_text)
    {
        std::vector<std::shared_ptr<IToken>> tokens;

        for(auto position = 0; position < input_text.size(); position++)
        {
            tokens.push_back(test_func_command(input_text, position));
            tokens.push_back(test_func_number_literal(input_text, position));
            tokens.push_back(test_func_operator(input_text[position]));
            tokens.push_back(test_func_string_leteral(input_text, position));
        }

        tokens.push_back(make_shared<Token>(TokenType::END, END));

        remove_nullptr_vec(tokens);
        return tokens;
    }

protected:
    std::wstring test_func_wstring_(const wstring& input, int& pos,
        const std::function<bool(wchar_t)>& func)
    {
        return test_st(input, pos, func);
    }

    shared_ptr<IToken> test_func_string_leteral(const wstring& input, int& pos)
    {
        if (isQuote(input[pos]))
            return std::make_shared<Token>(TokenType::STRING_LITERAL,
                    test_func_wstring_(input, pos,
                        test_bind(input[pos++], false)));
        return nullptr;
    }

    shared_ptr<IToken> test_func_number_literal(const wstring& input, int& pos)
    {
        if (IsDigit(input[pos]))
            return std::make_shared<Token>(TokenType::NUMBER_LITERAL,
                test_func_wstring_(input, pos, IsDigit));
        return nullptr;
    }

    shared_ptr<IToken> test_func_command(const wstring& input, int& pos)
    {
        if (IsSymbol(input[pos]))
        {
            wstring sb = test_st(input, pos, IsLetterOrDigit);
            if (test_func_(TYPE_DATA_, test_func_auto(sb)).first)
                return test_func_(TYPE_DATA_, test_func_auto(sb)).second;
            return make_shared<Token>(TokenType::ID, sb);
        }
        return nullptr;
    }

    shared_ptr<IToken> test_func_operator(const wchar_t ch)
    {
        if (test_func_(TYPE_CHAR_, test_bind(ch, true)).first)
            return test_func_(TYPE_CHAR_, test_bind(ch, true)).second;
        return nullptr;
    }

};




int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90;\nбуква: символ = \'ш\';\nтекст: строка = \"какой-то текст\";\n";

    std::wcout << L"Код:\n" << filename << std::endl;

    for (Lexer l; const auto& i : l.test_func(filename))
            std::wcout << static_cast<int>(i->getToken()) << ' '
                        << i->getValue() << std::endl;

    return 0;
}
