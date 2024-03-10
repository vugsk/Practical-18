
#ifndef TESTLEXER_HPP
#define TESTLEXER_HPP

#include <functional>
#include <memory>

#include "Vocabulary.hpp"


class TestLexer
{
    class TestToken;
    typedef std::shared_ptr<TestToken> tokenPtr;

public:
    explicit TestLexer(std::wstring input);

    TestLexer(const TestLexer& other)                = delete;
    TestLexer(TestLexer&& other) noexcept            = delete;
    TestLexer& operator=(const TestLexer& other)     = delete;
    TestLexer& operator=(TestLexer&& other) noexcept = delete;
    ~TestLexer()                                     = default;

    std::vector<tokenPtr> lexicalCodeAnalysis();

protected:
    typedef std::function<bool(wchar_t)> funcBoolWcharT;

    funcBoolWcharT test_func_bind(int pos, bool is) const;

    static std::function<bool(const std::wstring&)> test_func_auto(
        const std::wstring& sb);

    std::wstring test_st(int& position, const funcBoolWcharT& func) const;

    template<typename F>
    tokenPtr test_func_shared_ptr_num(int& pos, const TokenType token,
        const funcBoolWcharT& func, const F& func1)
    {
        if (func(_input[pos]))
            return test_func_factory(token, test_st(pos, func1(pos)));
        return test_func_null(NOTHING);
    }

    template<typename T>
    tokenPtr test_func_factory(const TokenType token, const T& value)
    {
        for (const auto i : TOKEN_TYPES)
            if (token == i)
                return std::make_shared<TestToken>(token, value);
        return test_func_none();
    }

    template<typename T>
    tokenPtr test_func_(const std::vector<std::pair<TokenType, T>>& vec,
            const std::function<bool(T)>& func,
            const tokenPtr& default_return)
    {
        for (const auto& [_token, ch] : vec)
            if (func(ch))
                return test_func_factory(_token, ch);
        return default_return;
    }

    static bool test_if_null_token(const tokenPtr& token,
        const std::wstring& value_if = NUL);


    tokenPtr test_func_none(const std::wstring& value = NONE);
    tokenPtr test_func_null(const std::wstring& value = NUL);

    tokenPtr command_operator(int pos);
    tokenPtr command_number(int& pos);
    tokenPtr command_string(int& pos);
    tokenPtr command_command(int& pos);

private:
    static const std::wstring NOTHING;
    static const size_t       MIN_SIZE_VEC;

    std::wstring _input;

    std::vector<std::function<tokenPtr(int&)>> test_vec
    {
        std::bind(&TestLexer::command_command, this, std::placeholders::_1),
        std::bind(&TestLexer::command_number, this, std::placeholders::_1),
        std::bind(&TestLexer::command_string, this, std::placeholders::_1),
        std::bind(&TestLexer::command_operator, this, std::placeholders::_1),
    };

    class TestToken
    {
    public:
        TestToken(const TestToken& other)                = delete;
        TestToken(TestToken&& other) noexcept            = delete;
        TestToken& operator=(const TestToken& other)     = delete;
        TestToken& operator=(TestToken&& other) noexcept = delete;
        ~TestToken()                                     = default;

        TestToken(TokenType token, std::wstring value);
        TestToken(TokenType token, wchar_t value);

        [[nodiscard]] const std::wstring& getValue() const;
        [[nodiscard]] TokenType           getToken() const;

    private:
        std::wstring _value;
        TokenType _token;
    };

};

#endif //TESTLEXER_HPP
