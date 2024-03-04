
#include <algorithm>
#include <iostream>
#include <utility>

#include <Config.hpp>

using namespace std;
using placeholders::_1;

class Lexer
{
public:
    explicit Lexer(wstring input_text)
        : m_input(std::move(input_text)), m_position(0) {}
    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer()                                 = default;

    vector<shared_ptr<Token>> test_func()
    {
        for(m_position = 0; m_position < m_input.size(); m_position++)
        {
            if (is_func(m_input[m_position]))
                m_token.push_back(make_shared<Token>(TokenType::STRING_LITERAL,
                    test_st(m_input, m_position,
                        bind(test_func_bool, _1, m_input[m_position++], false))));

            if (isdigit(m_input[m_position]))
                m_token.push_back(make_shared<Token>(TokenType::NUMBER_LITERAL,
                    test_st(m_input, m_position, IsDigit)));

            if (IsSymbol(m_input[m_position]))
                m_token.push_back(identifierOrKeyword());

            if (test_func_<wchar_t>(TYPE_CHAR_, bind(test_func_bool, m_input[m_position], _1, true)).first)
                m_token.push_back(test_func_<wchar_t>(TYPE_CHAR_, bind(test_func_bool, m_input[m_position], _1, true)).second);
       }

        m_token.push_back(make_shared<Token>(TokenType::END, END));
        return m_token;
    }

protected:
    shared_ptr<Token> identifierOrKeyword()
    {
        const wstring sb = test_st(m_input, m_position, IsLetterOrDigit);
        if (test_func_<wstring>(TYPE_DATA_, bind(ranges::equal, sb, _1)).first)
            return test_func_<wstring>(TYPE_DATA_, bind(ranges::equal, sb, _1)).second;
        return make_shared<Token>(TokenType::ID, sb);
    }

private:
    wstring m_input;
    int     m_position;
    vector<shared_ptr<Token>> m_token;
};


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
