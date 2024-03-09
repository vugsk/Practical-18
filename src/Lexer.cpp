
#include "Lexer.hpp"

#include "IToken.hpp"


using namespace func_itoken;



const std::wstring lexer::Lexer::NOTHING      = L"NOTHING";
const size_t       lexer::Lexer::MIN_SIZE_VEC = 4;



lexer::Lexer::Lexer(std::wstring input): m_input(std::move(input)) {}

std::vector<tokenPtr> lexer::Lexer::test_func()
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

std::function<bool(const wchar_t&)> lexer::Lexer::test_func_bind(const int pos,
    const bool is) const
{
    return [this, pos, is](const wchar_t i)
    {
        return is ? m_input[pos] == i : m_input[pos] != i;
    };
}

std::wstring lexer::Lexer::test_st(int& position,
    const std::function<bool(wchar_t)>& func) const
{
    std::wstring sb;
    while (func(m_input[position]))
        sb.push_back(m_input[position++]);
    return sb;
}

std::function<bool(const std::wstring&)> lexer::Lexer::test_func_auto(
    const std::wstring& sb)
{
    return [sb](const std::wstring& i)
    {
        return std::ranges::equal(sb, i);
    };
}

tokenPtr lexer::Lexer::command_operator(const int pos) const
{
    return test_func_(lexicon_cppon::OPERATORS, test_func_bind(pos, true),
                      test_func_null(NOTHING));
}

tokenPtr lexer::Lexer::command_number(int& pos)
{
    return test_func_shared_ptr_num(pos, number_literal, iswdigit,
        standard_functions::test_func_bind_lamda(iswdigit));
}

tokenPtr lexer::Lexer::command_string(int& pos)
{
    return test_func_shared_ptr_num(pos, string_literal,
        standard_functions::IsQuote, [this](int& i)
            { return test_func_bind(i++, false); });
}

tokenPtr lexer::Lexer::command_command(int& pos) const
{
    if (iswalpha(m_input[pos]))
    {
        const std::wstring io = test_st(pos, iswalnum);
        return test_func_(lexicon_cppon::DATA_TYPES, test_func_auto(io),
            test_func_id(io));
    }
    return test_func_null(NOTHING);
}

void lexer::Lexer::add(const std::function<tokenPtr(int)>& func) {
    test_vec.push_back(func);
}

void lexer::Lexer::remove() {
    if (test_vec.size() == MIN_SIZE_VEC)
        return;
    test_vec.pop_back();
}
