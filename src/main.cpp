
#include <iostream>

#include <algorithm>

#include <Config.hpp>

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

vector<Token*> test_func(const wstring& input_text)
{
    input = input_text;

    vector<Token*> token;
    for(pos = 0; pos < input.size(); pos++)
    {
        if (input[pos] == STRING_LITERAL.first || input[pos] == STRING_LITERAL.second)
            token.push_back(new Token(TokenType::STRING_LITERAL, test_func_wstring(input[pos])));

        else if (isdigit(input[pos]))
            token.push_back(new Token(TokenType::NUMBER_LITERAL, integer()));

        else if (IsSymbol(input[pos]))
            token.push_back(identifierOrKeyword());

        if (input[pos] == COLON)
            token.push_back(new Token(TokenType::COLON, L":"));

        else if (input[pos] == SEMICOLON)
            token.push_back(new Token(TokenType::SEMICOLON, L";"));

        else if (input[pos] == ASSIGNMENT)
            token.push_back(new Token(TokenType::ASSIGNMENT, L"="));
    }

    token.push_back(new Token(TokenType::END, END));
    return token;
}

wstring test_func_wstring(const wchar_t quote)
{
    wstring sb;
    pos++;
    while (input[pos] != input.size() - 1 && input[pos] != quote)
        sb.push_back(input[pos++]);
    return sb;
}

Token* identifierOrKeyword()
{
    wstring sb;
    while (input[pos] != input.size() - 1 && IsLetterOrDigit(input[pos]))
        sb.push_back(input[pos++]);

    if (ranges::equal(sb, NUMBER))
        return new Token(TokenType::NUMBER_DATATYPE, sb);
    if (ranges::equal(sb, STRING))
        return new Token(TokenType::STRING_DATATYPE, sb);
    if (ranges::equal(sb, CHARACTER))
        return new Token(TokenType::CHARACTER_DATATYPE, sb);

    return new Token(TokenType::ID, sb);
}


wstring integer()
{
    wstring sb;
    while (input[pos] != input.size() - 1 && IsDigit(input[pos]))
        sb.push_back(input[pos++]);
    return sb;
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