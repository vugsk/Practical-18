
#ifndef TESTLEXER_HPP
#define TESTLEXER_HPP

#include <functional>
#include <memory>

#include "Token.hpp"
#include "Vocabulary.hpp"


class Lexer
{
    typedef std::shared_ptr<IToken> tokenPointer;

public:
    explicit Lexer(std::wstring input);

    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer()                                 = default;

    std::vector<tokenPointer> lexicalCodeAnalysis();

protected:
    typedef std::function<bool(wchar_t)> funcBoolWcharT;

    [[nodiscard]] funcBoolWcharT checkingCharacterMatchesPosition(int pos,
        bool is) const;

    static std::function<bool(const std::wstring&)> сompareStrings(
        const std::wstring& sb);

    std::wstring extractString(int& position, const funcBoolWcharT& func) const;

    template<typename F>
    tokenPointer createTokenWithExtractedString(int& pos, const TokenType token,
        const funcBoolWcharT& func, const F& func1)
    {
        if (func(_input[pos]))
            return createToken(token, extractString(pos, func1(pos)));
        return createNullToken(NOTHING);
    }

    template<typename T>
    tokenPointer createToken(const TokenType token, const T& value)
    {
        for (const auto i : TOKEN_TYPES)
            if (token == i)
                return std::make_shared<Token>(token, value);
        return createNoneToken();
    }

    template<typename T>
    tokenPointer findToken(const std::vector<std::pair<TokenType, T>>& vec,
            const std::function<bool(T)>& func,
            const tokenPointer& default_return)
    {
        for (const auto& [_token, ch] : vec)
            if (func(ch))
                return createToken(_token, ch);
        return default_return;
    }

    static bool isNullToken(const tokenPointer& token,
        const std::wstring& value_if = NUL);


    tokenPointer createNoneToken(const std::wstring& value = NONE);
    tokenPointer createNullToken(const std::wstring& value = NUL);

    tokenPointer findOperatorAtPosition(int pos);
    tokenPointer createNumberToken(int& pos);
    tokenPointer createStringToken(int& pos);
    tokenPointer createCommandToken(int& pos);

private:
    static const std::wstring NOTHING;
    static const size_t       MIN_SIZE_VEC;

    std::wstring _input;

    const std::vector<std::function<tokenPointer(int&)>> _tokenMakers
    {
        std::bind(&Lexer::createCommandToken, this, std::placeholders::_1),
        std::bind(&Lexer::createNumberToken, this, std::placeholders::_1),
        std::bind(&Lexer::createStringToken, this, std::placeholders::_1),
        std::bind(&Lexer::findOperatorAtPosition, this, std::placeholders::_1),
    };

};

#endif //TESTLEXER_HPP
