#ifndef LEXER_HPP
#define LEXER_HPP

#include <Token.hpp>

#include "ILexer.hpp"

namespace lexer
{

template<typename T>
func_itoken::tokenPtr test_func_(
        const std::vector<std::pair<TokenType, T>>& vec,
        const std::function<bool(const T&)>& func,
        const func_itoken::tokenPtr& default_return =
            func_itoken::test_func_none())
{
    for (const auto& [_token, ch] : vec)
        if (func(ch))
            return test_func_factory(_token, ch);
    return default_return;
}

class Lexer final : public ilexer::ILexer
{
public:
    explicit Lexer(std::wstring input);
    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer() override = default;

    std::vector<func_itoken::tokenPtr> test_func() override;

protected:
    std::function<bool(const wchar_t&)> test_func_bind(int pos, bool is) const;

    static std::function<bool(const std::wstring&)> test_func_auto(
        const std::wstring& sb);

    std::wstring test_st(int& position,
        const std::function<bool(wchar_t)>& func) const;

    template<typename F>
    func_itoken::tokenPtr test_func_shared_ptr_num(int& pos,
        const TokenType token, const std::function<bool(wchar_t)>& func,
        const F& func1)
    {
        if (func(m_input[pos]))
            return test_func_factory(token, test_st(pos, func1(pos)));
        return func_itoken::test_func_null(NOTHING);
    }

    func_itoken::tokenPtr command_operator(int pos) const;
    func_itoken::tokenPtr command_number(int& pos);
    func_itoken::tokenPtr command_string(int& pos);
    func_itoken::tokenPtr command_command(int& pos) const;

    void add(const std::function<func_itoken::tokenPtr(int)>& func);
    void remove();

private:
    static const std::wstring NOTHING;
    static const size_t       MIN_SIZE_VEC;

    std::wstring m_input;

    std::vector<std::function<func_itoken::tokenPtr(int&)>> test_vec
    {
        std::bind(&Lexer::command_command, this, std::placeholders::_1),
        std::bind(&Lexer::command_number, this, std::placeholders::_1),
        std::bind(&Lexer::command_string, this, std::placeholders::_1),
        std::bind(&Lexer::command_operator, this, std::placeholders::_1),
    };
};

}

#endif //LEXER_HPP
