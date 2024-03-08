
#include "Config.hpp"

#include <codecvt>
#include <locale>


bool Is_func_test(const int to, const int from, const wchar_t ch)
{
    for (auto i = to; i < from + 1; i++)
        if (i == ch)
            return true;
    return false;
}

bool Is_func_test(const std::pair<int, int>& p, const wchar_t ch)
{
    return Is_func_test(p.first, p.second, ch);
}

bool IsDigit(const wchar_t number)
{
    return Is_func_test(45, 57, number);
}

bool IsSpace(const wchar_t _ch)
{
    return _ch == SPACE;
}

bool IsSymbol(const wchar_t _ch)
{
    return Is_func_test(1072, 1103, _ch);
}

bool IsLetterOrDigit(const wchar_t _ch)
{
    return IsDigit(_ch) || IsSymbol(_ch);
}

bool isQuote(const wchar_t ch)
{
    return ch == CHARACTER_LITERAL || ch == STRING_LITERAL;
}

std::wstring ConvertString(const std::string& string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(string.c_str());
    return wtext;
}

std::wstring test_st(const std::wstring& _input, int& position,
    const std::function<bool(wchar_t)>& func)
{
    std::wstring sb;
    while (func(_input[position]))
        sb.push_back(_input[position++]);
    return sb;
}

std::function<bool(const wchar_t&)> test_bind(const wchar_t ch, const bool is)
{
    return [ch, is](const wchar_t i) -> bool
    {
        return is ? ch == i : ch != i;
    };
}

std::function<bool(const std::wstring&)> test_func_auto(const std::wstring& sb)
{
    return [sb](const std::wstring& i) -> bool
    {
        return std::ranges::equal(sb, i);
    };
}

void remove_nullptr_vec(std::vector<std::shared_ptr<IToken>>& tokens) {
    std::erase_if(tokens, [](const std::shared_ptr<IToken>& token) -> bool
    {
        return token == nullptr;
    });
}

bool test_if_none_token(const std::shared_ptr<IToken>& token)
{
    return token->getToken() == TokenType::none || token->getValue() == NONE;
}


std::shared_ptr<IToken> test_func_string_leteral(const std::wstring& value)
{
    return test_func_factory(TokenType::string_literal, value);
}

std::shared_ptr<IToken> test_func_number_leteral(const std::wstring& value)
{
    return test_func_factory(TokenType::number_literal, value);
}

std::shared_ptr<IToken> test_func_id(const std::wstring& value)
{
    return test_func_factory(TokenType::id, value);
}

std::shared_ptr<IToken> test_func_none(const std::wstring& value)
{
    return test_func_factory(TokenType::none, value);
}

std::shared_ptr<IToken> test_func_end(const std::wstring& value)
{
    return test_func_factory(TokenType::end, value);
}

std::shared_ptr<IToken> test_func_factory(const TokenType token,
                                          const std::wstring& value)
{
    for (const auto i : TOKEN_TYPES)
        if (token == i)
            return std::make_shared<Token>(token, value);
    return test_func_none();
}

bool test_func_check_class_token(const std::shared_ptr<IToken>& token)
{
    return !(token->getToken() == TokenType::none || token->getValue() == NONE);
}

