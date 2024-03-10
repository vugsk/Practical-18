
#include "Lexer.hpp"

#include <algorithm>

const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;


Lexer::Lexer(std::wstring input)
    : _input(std::move(input)) {}

std::vector<Lexer::tokenPtr> Lexer::lexicalCodeAnalysis()
{
    std::vector<tokenPtr> m_tokens;
    for(auto pos = 0; pos < _input.size(); pos++)
    {
        for (const auto& i : test_vec)
        {
            const tokenPtr io = i(pos);
            if (test_if_null_token(io, NOTHING))
                m_tokens.push_back(io);
        }
    }

    m_tokens.push_back(test_func_factory(end, END));
    return m_tokens;
}

Lexer::funcBoolWcharT Lexer::test_func_bind(int pos, bool is) const
{
    return [this, pos, is](const wchar_t i) -> bool
    {
        return is ? _input[pos] == i : _input[pos] != i;
    };
}

std::function<bool(const std::wstring&)> Lexer::test_func_auto(
    const std::wstring& sb)
{
    return [sb](const std::wstring& i) -> bool
    {
        return std::ranges::equal(sb, i);
    };
}

std::wstring Lexer::test_st(int& position, const funcBoolWcharT& func) const
{
    std::wstring sb;
    while (func(_input[position]))
        sb.push_back(_input[position++]);
    return sb;
}

bool Lexer::test_if_null_token(const tokenPtr& token,
    const std::wstring& value_if)
{
    return token->getToken() != null || token->getValue() != value_if;
}

Lexer::tokenPtr Lexer::test_func_none(const std::wstring& value)
{
    return test_func_factory(none, value);
}

Lexer::tokenPtr Lexer::test_func_null(const std::wstring& value)
{
    return test_func_factory(null, value);
}

Lexer::tokenPtr Lexer::command_operator(int pos)
{
    return test_func_(OPERATORS, test_func_bind(pos, true),
                      test_func_null(NOTHING));
}

Lexer::tokenPtr Lexer::command_number(int& pos)
{
    return test_func_shared_ptr_num(pos, number_literal,
        iswdigit, test_func_bind_lamda(iswdigit));
}

Lexer::tokenPtr Lexer::command_string(int& pos)
{
    return test_func_shared_ptr_num(pos, string_literal,
        IsQuote, [this](int& i)
            { return test_func_bind(i++, false); });
}

Lexer::tokenPtr Lexer::command_command(int& pos)
{
    if (iswalpha(_input[pos]))
    {
        const std::wstring io = test_st(pos, iswalnum);
        return test_func_<std::wstring>(DATA_TYPES, test_func_auto(io),
            test_func_factory(id, io));
    }
    return test_func_null(NOTHING);
}
