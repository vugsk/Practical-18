
#include <iostream>

#include <algorithm>
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

static wstring input;
static auto    pos   = 0;
static wchar_t ch;

void SkipSpace();
void Advace();
wstring test_func_wstring(wchar_t quote);
wstring integer();

vector<Token*> test_func(const wstring& input_text)
{
    input = input_text;
    ch = input_text[pos];

    vector<Token*> token;

    while (pos != input_text.size() - 1)
    {
        if (ch == SPACE)
        {
            SkipSpace();
        }
        else if (ch == COLON)
        {
            token.push_back(new Token(TokenType::COLON, L":"));
            Advace();
        }
        else if (ch == SEMICOLON)
        {
            token.push_back(new Token(TokenType::SEMICOLON, L";"));
            Advace();
        }
        else if (ch == ASSIGNMENT)
        {
            token.push_back(new Token(TokenType::ASSIGNMENT, L"="));
            Advace();
        }
        else if (ch == STRING_LITERAL.first || ch == STRING_LITERAL.second)
        {
            token.push_back(new Token(TokenType::STRING_LITERAL,
                test_func_wstring(ch)));
            Advace();
        }
        else if (isdigit(ch))
        {
            token.push_back(new Token(TokenType::STRING_LITERAL, integer()));
            Advace();
        }
        else
        {
            Advace();
        }
    }

    token.push_back(new Token(TokenType::END, L"NUL"));

    return token;
}

void Advace()
{
    pos++;
    if (pos > input.length() - 1) {
        ch = '\0';
    }
    else {
        ch = input[pos];
    }
}

void SkipSpace()
{
    while (ch != input.size() - 1 && ch == ' ')
        Advace();
}

wstring test_func_wstring(const wchar_t quote)
{
    wstring sb;
    Advace();
    while (ch != input.size() - 1 && ch != quote)
    {
        sb.push_back(ch);
        Advace();
    }

    return sb;
}

bool isDigit(const wchar_t number)
{
    for(const auto i : L"1234567890")
        if (number == i)
            return true;
    return false;
}

wstring integer()
{
    wstring sb;
     while (ch != input.size() - 1 && isDigit(ch)) {
        sb.push_back(ch);
        Advace();
    }
    return sb;
}



int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90; буква: символ = \'ш\'; текст: строка = \"какой-то текст\";";
    std::wcout << filename << std::endl;

    std::vector<Token*> tokens = test_func(filename);

    for (const auto i : tokens)
    {
        std::wcout << static_cast<int>(i->getToken()) << ' '
                    << i->getValue() << std::endl;
    }

    for (auto& i : tokens)
    {
        delete i;
    }
    tokens.clear();

    return 0;
}