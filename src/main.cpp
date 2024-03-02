
#include <iostream>

#include <Config.hpp>
#include <utility>

using namespace std;

class Token
{
public:
    Token(const TokenType token, wstring value)
        : _token(token), _value(std::move(value)) {}

    [[nodiscard]] TokenType getToken() const
    {
        return _token;
    }

    [[nodiscard]] wstring getValue() const
    {
        return _value;
    }

private:
    TokenType _token;
    wstring _value;

};


//! doing
vector<Token> test_func(const wstring& input_text)
{



    return {};
}



int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90; буква: символ = ш; текст: строка = какой-то текст;";

    const vector<Token> token = test_func(filename);
    for (const auto& i : token)
    {
        std::wcout << i.getValue() << std::endl;
    }

    return 0;
}