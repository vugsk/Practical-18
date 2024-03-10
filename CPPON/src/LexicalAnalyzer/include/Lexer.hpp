
#ifndef LEXER_HPP
#define LEXER_HPP

#include <functional>
#include <string>

#include "ILexer.hpp"
#include "Vocabulary.hpp"



class IToken
{
public:
    virtual                            ~IToken() = default;
    [[nodiscard]] virtual TokenType    getToken() const = 0;
    [[nodiscard]] virtual std::wstring getValue() const = 0;
};

typedef std::shared_ptr<IToken> tokenPtr;

bool test_if_none_token(const tokenPtr& token);
bool test_if_null_token(const tokenPtr& token,
    const std::wstring& value_if = NUL);

tokenPtr test_func_string_leteral(const std::wstring& value);
tokenPtr test_func_number_leteral(const std::wstring& value);
tokenPtr test_func_id(const std::wstring& value);
tokenPtr test_func_none(const std::wstring& value = NONE);
tokenPtr test_func_end(const std::wstring& value = END);
tokenPtr test_func_null(const std::wstring& value = NUL);


class Token final : public IToken
{
public:
    Token(const Token& other)                = delete;
    Token(Token&& other) noexcept            = delete;
    Token& operator=(const Token& other)     = delete;
    Token& operator=(Token&& other) noexcept = delete;
    ~Token() override                        = default;

    Token(TokenType token, std::wstring value);
    Token(TokenType token, wchar_t value);

    [[nodiscard]] TokenType getToken() const override;
    [[nodiscard]] std::wstring getValue() const override;

private:
    TokenType    _token;
    std::wstring _value;
};



template<typename T>
tokenPtr test_func_factory(const TokenType token,
    const T& value)
{
    for (const auto i : TOKEN_TYPES)
        if (token == i)
            return std::make_shared<Token>(token, value);
    return test_func_none();
}




template<typename T>
tokenPtr test_func_(
        const std::vector<std::pair<TokenType, T>>& vec,
        const std::function<bool(const T&)>& func,
        const tokenPtr& default_return =
            test_func_none())
{
    for (const auto& [_token, ch] : vec)
        if (func(ch))
            return test_func_factory(_token, ch);
    return default_return;
}

class Lexer final : public ILexer
{
public:
    explicit Lexer(std::wstring input);
    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer() override = default;

    std::vector<tokenPtr> lexicalCodeAnalysis() override;

protected:
    std::function<bool(const wchar_t&)> test_func_bind(int pos, bool is) const;

    static std::function<bool(const std::wstring&)> test_func_auto(
        const std::wstring& sb);

    std::wstring test_st(int& position,
        const std::function<bool(wchar_t)>& func) const;

    template<typename F>
    tokenPtr test_func_shared_ptr_num(int& pos,
        const TokenType token, const std::function<bool(wchar_t)>& func,
        const F& func1)
    {
        if (func(m_input[pos]))
            return test_func_factory(token, test_st(pos, func1(pos)));
        return test_func_null(NOTHING);
    }

    tokenPtr command_operator(int pos) const;
    tokenPtr command_number(int& pos);
    tokenPtr command_string(int& pos);
    tokenPtr command_command(int& pos) const;

    void add(const std::function<tokenPtr(int)>& func);
    void remove();

private:
    static const std::wstring NOTHING;
    static const size_t       MIN_SIZE_VEC;

    std::wstring m_input;

    std::vector<std::function<tokenPtr(int&)>> test_vec
    {
        std::bind(&Lexer::command_command, this, std::placeholders::_1),
        std::bind(&Lexer::command_number, this, std::placeholders::_1),
        std::bind(&Lexer::command_string, this, std::placeholders::_1),
        std::bind(&Lexer::command_operator, this, std::placeholders::_1),
    };
};

#endif //LEXER_HPP
