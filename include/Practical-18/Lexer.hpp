#ifndef LEXER_HPP
#define LEXER_HPP

#include <functional>

#include "ILexer.hpp"
#include "Token.hpp"

namespace lexer
{

template<typename T>
std::shared_ptr<itoken::IToken> test_func_(
        const std::vector<std::pair<TokenType, T>>& vec,
        const std::function<bool(const T&)>& func,
        const std::shared_ptr<itoken::IToken>& default_return =
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

    std::vector<std::shared_ptr<itoken::IToken>> test_func() override;

protected:
    std::function<bool(const wchar_t&)> test_func_bind(int pos, bool is) const;

    std::wstring test_st(int& position,
        const std::function<bool(wchar_t)>& func) const;

    template<typename F>
    std::shared_ptr<itoken::IToken> test_func_shared_ptr_num(int& pos,
        const TokenType token, const std::function<bool(wchar_t)>& func,
        const F& func1)
    {
        if (func(m_input[pos]))
            return test_func_factory(token, test_st(pos, func1(pos)));
        return func_itoken::test_func_null(NOTHING);
    }

    std::shared_ptr<itoken::IToken> command_operator(int pos) const;
    std::shared_ptr<itoken::IToken> command_number(int& pos);
    std::shared_ptr<itoken::IToken> command_string(int& pos);
    std::shared_ptr<itoken::IToken> command_command(int& pos) const;

    void add(const std::function<std::shared_ptr<itoken::IToken>(int)>& func);
    void remove();

private:
    static const std::wstring NOTHING;
    static const size_t       MIN_SIZE_VEC;

    std::vector<std::shared_ptr<itoken::IToken>> m_tokens;
    std::wstring                         m_input;

    std::vector<std::function<std::shared_ptr<itoken::IToken>(int&)>> test_vec
    {
        [this](int& pos) {return command_command(pos);},
        [this](int& pos) {return command_number(pos);},
        [this](int& pos) {return command_string(pos);},
        [this](const int pos) {return command_operator(pos);},
    };
};

}

#endif //LEXER_HPP
