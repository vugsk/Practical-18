
#include <algorithm>
#include <functional>
#include <iostream>

#include <Config.hpp>

using namespace std;
using placeholders::_1;

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

static wstring input;
static int     pos;


wstring test_func_wstring(const wchar_t quote)
{
    pos++;
    return test_st(input, pos, [quote](const wchar_t i) { return i != quote; });
}

template<typename F>
pair<bool, Token*> test_func_(const vector<pair<TokenType, wstring>>& vec,
    const F& func)
{
    for (const auto& [_token, ch] : vec)
        if (func(ch))
            return {true, new Token(_token, ch)};
    return {false, nullptr};
}

Token* identifierOrKeyword()
{
    const wstring sb = test_st(input, pos, IsLetterOrDigit);
    if (test_func_(TYPE_DATA_, bind(ranges::equal, sb, _1)).first)
        return test_func_(TYPE_DATA_, bind(ranges::equal, sb, _1)).second;
    return new Token(TokenType::ID, sb);
}

vector<Token*> test_func(const wstring& input_text)
{
    input = input_text;
    vector<Token*> token;
    for(pos = 0; pos < input.size(); pos++)
    {
        if (is_func(input[pos]))
            token.push_back(new Token(TokenType::STRING_LITERAL,
                test_func_wstring(input[pos])));

        if (isdigit(input[pos]))
            token.push_back(new Token(TokenType::NUMBER_LITERAL,
                test_st(input, pos, IsDigit)));

        if (IsSymbol(input[pos]))
            token.push_back(identifierOrKeyword());

        if (test_func_(TYPE_CHAR_, bind(test_func_bool, input[pos], _1)).first)
            token.push_back(test_func_(TYPE_CHAR_, bind(test_func_bool, input[pos], _1)).second);
    }

    token.push_back(new Token(TokenType::END, END));
    return token;
}



int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90;\nбуква: символ = \'ш\';\nтекст: строка = \"какой-то текст\";\n";

    std::wcout << L"Код:\n" << filename << std::endl;

    const std::vector<Token*> tokens = test_func(filename);
    for (const auto i : tokens)
        std::wcout << static_cast<int>(i->getToken()) << ' '
                    << i->getValue() << std::endl;

    for (const auto& i : tokens)
        delete i;

    return 0;
}