
#ifndef TESTLEXER_HPP
#define TESTLEXER_HPP

#include <functional>
#include <memory>

#include "Token.hpp"
#include "Vocabulary.hpp"


class Lexer
{
    typedef std::shared_ptr<IToken> tokenPtr;

public:
    explicit Lexer(std::wstring input);

    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer()                                     = default;

    std::vector<tokenPtr> lexicalCodeAnalysis();

protected:
    typedef std::function<bool(wchar_t)> funcBoolWcharT;

    funcBoolWcharT checkingCharacterMatchesPosition(int pos, bool is) const;

    static std::function<bool(const std::wstring&)> сompareStrings(
        const std::wstring& sb);

    std::wstring extractString(int& position, const funcBoolWcharT& func) const;

    template<typename F>
    tokenPtr createTokenWithExtractedString(int& pos, const TokenType token,
        const funcBoolWcharT& func, const F& func1)
    {
        if (func(_input[pos]))
            return createToken(token, extractString(pos, func1(pos)));
        return createNullToken(NOTHING);
    }

    template<typename T>
    tokenPtr createToken(const TokenType token, const T& value)
    {
        for (const auto i : TOKEN_TYPES)
            if (token == i)
                return std::make_shared<Token>(token, value);
        return createNoneToken();
    }

    template<typename T>
    tokenPtr findToken(const std::vector<std::pair<TokenType, T>>& vec,
            const std::function<bool(T)>& func,
            const tokenPtr& default_return)
    {
        for (const auto& [_token, ch] : vec)
            if (func(ch))
                return createToken(_token, ch);
        return default_return;
    }

    static bool isNullToken(const tokenPtr& token,
        const std::wstring& value_if = NUL);


    tokenPtr createNoneToken(const std::wstring& value = NONE);
    tokenPtr createNullToken(const std::wstring& value = NUL);

    tokenPtr findOperatorAtPosition(int pos);
    tokenPtr createNumberToken(int& pos);
    tokenPtr createStringToken(int& pos);
    tokenPtr createCommandToken(int& pos);

private:
    static const std::wstring NOTHING;
    static const size_t       MIN_SIZE_VEC;

    std::wstring _input;

    const std::vector<std::function<tokenPtr(int&)>> test_vec
    {
        std::bind(&Lexer::createCommandToken, this, std::placeholders::_1),
        std::bind(&Lexer::createNumberToken, this, std::placeholders::_1),
        std::bind(&Lexer::createStringToken, this, std::placeholders::_1),
        std::bind(&Lexer::findOperatorAtPosition, this, std::placeholders::_1),
    };

};

#endif //TESTLEXER_HPP
