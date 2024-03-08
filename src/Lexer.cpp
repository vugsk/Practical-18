
#include "Lexer.hpp"

#include "IToken.hpp"

using namespace itoken;
using namespace func_itoken;
using namespace func_base;
using namespace type_char_literals;

const std::wstring lexer::Lexer::NOTHING      = L"NOTHING";
const size_t       lexer::Lexer::MIN_SIZE_VEC = 4;

lexer::Lexer::Lexer(std::wstring input): m_input(std::move(input)) {}

std::vector<std::shared_ptr<IToken>> lexer::Lexer::test_func()
{
    for(auto pos = 0; pos < m_input.size(); pos++)
    {
        for (const auto& i : test_vec)
        {
            const std::shared_ptr<IToken> io = i(pos);
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
    return test_bind(m_input[pos], is); // return function
}

std::wstring lexer::Lexer::test_st(int& position,
                            const std::function<bool(wchar_t)>& func) const
{
    std::wstring sb;
    while (func(m_input[position]))
        sb.push_back(m_input[position++]);
    return sb;
}

std::shared_ptr<IToken> lexer::Lexer::command_operator(const int pos) const
{
    return test_func_(TYPE_CHAR_, test_func_bind(pos, true),
                      test_func_null(NOTHING));
}

std::shared_ptr<IToken> lexer::Lexer::command_number(int& pos)
{
    return test_func_shared_ptr_num(pos, number_literal, IsDigit,
                                    test_func_bind_lamda(IsDigit));
}

std::shared_ptr<IToken> lexer::Lexer::command_string(int& pos)
{
    return test_func_shared_ptr_num(pos, string_literal, isQuote,
        [this](int& i)
            { return test_func_bind(i++, false); });
}

std::shared_ptr<IToken> lexer::Lexer::command_command(int& pos) const
{
    if (IsSymbol(m_input[pos]))
        return test_func_(TYPE_DATA_, test_func_auto(test_st(pos,
            IsLetterOrDigit)), test_func_id(test_st(pos, IsLetterOrDigit)));
    return test_func_null(NOTHING);
}

void lexer::Lexer::add(const std::function<std::shared_ptr<IToken>(int)>& func) {
    test_vec.push_back(func);
}

void lexer::Lexer::remove() {
    if (test_vec.size() == MIN_SIZE_VEC)
        return;
    test_vec.pop_back();
}
