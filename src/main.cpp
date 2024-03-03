
#include <algorithm>
#include <iostream>

#include <Config.hpp>

using namespace std;
using placeholders::_1;

static wstring input;
static int     pos;

wstring test_func_wstring(const wchar_t quote)
{
    pos++;
    return test_st(input, pos, bind(test_func_bool, _1, quote, false));
}

shared_ptr<Token> identifierOrKeyword()
{
    const wstring sb = test_st(input, pos, IsLetterOrDigit);
    if (test_func_<wstring>(TYPE_DATA_, bind(ranges::equal, sb, _1)).first)
        return test_func_<wstring>(TYPE_DATA_, bind(ranges::equal, sb, _1)).second;
    return make_shared<Token>(TokenType::ID, sb);
}

// pair<bool, shared_ptr<Token>> test_func_pair()
// {
//     if (is_func(input[pos]))
//         make_shared<Token>(TokenType::STRING_LITERAL, test_func_wstring(input[pos]));
//     return {false, nullptr};
// }

vector<shared_ptr<Token>> test_func(const wstring& input_text)
{
    input = input_text;
    vector<shared_ptr<Token>> token;
    for(pos = 0; pos < input.size(); pos++)
    {
        if (is_func(input[pos]))
            token.push_back(make_shared<Token>(TokenType::STRING_LITERAL,
                test_func_wstring(input[pos])));

        if (isdigit(input[pos]))
            token.push_back(make_shared<Token>(TokenType::NUMBER_LITERAL,
                test_st(input, pos, IsDigit)));

        if (IsSymbol(input[pos]))
            token.push_back(identifierOrKeyword());

        if (test_func_<wchar_t>(TYPE_CHAR_, bind(test_func_bool, input[pos], _1, true)).first)
            token.push_back(test_func_<wchar_t>(TYPE_CHAR_, bind(test_func_bool, input[pos], _1, true)).second);
    }

    token.push_back(make_shared<Token>(TokenType::END, END));
    return token;
}




int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename =
        L"номер: число = 90;\nбуква: символ = \'ш\';\nтекст: строка = \"какой-то текст\";\n";

    std::wcout << L"Код:\n" << filename << std::endl;

    for (const auto& i : test_func(filename))
        std::wcout << static_cast<int>(i->getToken()) << ' '
                    << i->getValue() << std::endl;


    return 0;
}
