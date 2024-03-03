
#include <algorithm>
#include <iostream>

#include <Config.hpp>
#include <functional>

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

static wstring input;
static int     pos;

wstring test_func_wstring(wchar_t quote);
wstring integer();
Token* identifierOrKeyword();

// template<typename T, typename F>
// Token* test_func_token_gen(const vector<pair<TokenType, T>>& vec,
//     const F& func, const wstring& ch, bool is);


vector<Token*> test_func(const wstring& input_text)
{
    input = input_text;
    vector<Token*> token;
    for(pos = 0; pos < input.size(); pos++)
    {
        if (is_func(input[pos]))
            token.push_back(new Token(TokenType::STRING_LITERAL, test_func_wstring(input[pos])));

        else if (isdigit(input[pos]))
            token.push_back(new Token(TokenType::NUMBER_LITERAL, integer()));

        else if (IsSymbol(input[pos]))
            token.push_back(identifierOrKeyword());

        for (const auto& [_token, ch] : TYPE_CHAR_)
            if (input[pos] == ch[0])
                token.push_back(new Token(_token, ch));
    }

    token.push_back(new Token(TokenType::END, END));
    return token;
}


template<typename F>
wstring test_st(const F& func)
{
    wstring sb;
    while (func(input[pos]))
        sb.push_back(input[pos++]);
    return sb;
}


wstring test_func_wstring(const wchar_t quote)
{
    pos++;
    return test_st([quote](const wchar_t i) { return i != quote; });
}

// template<typename T, typename F>
// Token* test_func_token_gen(const vector<pair<TokenType, T>>& vec,
//     const F& func, const wstring& ch, const bool is)
// {
//     for (const auto& [token, type_data] : vec)
//         if (func(ch, type_data))
//             return new Token(token, ch);
//
//     if ((!IsSpace(input[pos]) || !isEnter(input[pos]) ||
//         !isQuote(input[pos])) && is)
//             return new Token(TokenType::END, END);
//     return new Token(TokenType::ID, ch);
// }

Token* identifierOrKeyword()
{
    const wstring sb = test_st(IsLetterOrDigit);
    for (const auto& [token, type_data] : TYPE_DATA_)
        if (ranges::equal(sb, type_data))
            return new Token(token, sb);
    return new Token(TokenType::ID, sb);
}

wstring integer()
{
    return test_st(IsDigit);
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