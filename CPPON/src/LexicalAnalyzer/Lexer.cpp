
#include "Lexer.hpp"



bool test_if_none_token(const std::shared_ptr<IToken>& token)
{
    return token->getToken() != none || token->getValue() != NONE;
}

bool test_if_null_token(const std::shared_ptr<IToken>& token,
    const std::wstring& value_if)
{
    return token->getToken() != null || token->getValue() != value_if;
}


std::shared_ptr<IToken> test_func_string_leteral(
    const std::wstring& value)
{
    return test_func_factory(string_literal, value);
}

std::shared_ptr<IToken> test_func_number_leteral(
    const std::wstring& value)
{
    return test_func_factory(number_literal, value);
}

std::shared_ptr<IToken> test_func_id(const std::wstring& value)
{
    return test_func_factory(id, value);
}

std::shared_ptr<IToken> test_func_none(const std::wstring& value)
{
    return test_func_factory(none, value);
}

std::shared_ptr<IToken> test_func_end(const std::wstring& value)
{
    return test_func_factory(end, value);
}

std::shared_ptr<IToken> test_func_null(const std::wstring& value)
{
    return test_func_factory(null, value);
}




Token::Token(const TokenType token, std::wstring value)
    : _token(token), _value(std::move(value)) {}

Token::Token(const TokenType token, const wchar_t value)
    : _token(token)
{
    _value = value;
}

TokenType Token::getToken() const
{
    return _token;
}

std::wstring Token::getValue() const
{
    return _value;
}




const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;



Lexer::Lexer(std::wstring input): m_input(std::move(input)) {}

std::vector<tokenPtr> Lexer::lexicalCodeAnalysis()
{
    std::vector<tokenPtr> m_tokens;
    for(auto pos = 0; pos < m_input.size(); pos++)
    {
        for (const auto& i : test_vec)
        {
            const tokenPtr io = i(pos);
            if (test_if_null_token(io, NOTHING))
                m_tokens.push_back(io);
        }
    }

    m_tokens.push_back(test_func_end());
    return m_tokens;
}

std::function<bool(const wchar_t&)> Lexer::test_func_bind(const int pos,
    const bool is) const
{
    return [this, pos, is](const wchar_t i)
    {
        return is ? m_input[pos] == i : m_input[pos] != i;
    };
}

std::wstring Lexer::test_st(int& position,
    const std::function<bool(wchar_t)>& func) const
{
    std::wstring sb;
    while (func(m_input[position]))
        sb.push_back(m_input[position++]);
    return sb;
}

std::function<bool(const std::wstring&)> Lexer::test_func_auto(
    const std::wstring& sb)
{
    return [sb](const std::wstring& i)
    {
        return std::ranges::equal(sb, i);
    };
}

tokenPtr Lexer::command_operator(const int pos) const
{
    return test_func_(OPERATORS, test_func_bind(pos, true),
                      test_func_null(NOTHING));
}

tokenPtr Lexer::command_number(int& pos)
{
    return test_func_shared_ptr_num(pos, number_literal, iswdigit,
        test_func_bind_lamda(iswdigit));
}

tokenPtr Lexer::command_string(int& pos)
{
    return test_func_shared_ptr_num(pos, string_literal,
        IsQuote, [this](int& i)
            { return test_func_bind(i++, false); });
}

tokenPtr Lexer::command_command(int& pos) const
{
    if (iswalpha(m_input[pos]))
    {
        const std::wstring io = test_st(pos, iswalnum);
        return test_func_(DATA_TYPES, test_func_auto(io),
            test_func_id(io));
    }
    return test_func_null(NOTHING);
}

void Lexer::add(const std::function<tokenPtr(int)>& func) {
    test_vec.push_back(func);
}

void Lexer::remove() {
    if (test_vec.size() == MIN_SIZE_VEC)
        return;
    test_vec.pop_back();
}