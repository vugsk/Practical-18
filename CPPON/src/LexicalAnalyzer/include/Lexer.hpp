
#ifndef TESTLEXER_HPP
#define TESTLEXER_HPP

#include <functional>
#include <memory>

#include <TypeToken.hpp>
#include "IToken.hpp"

[[nodiscard]] inline bool IsQuote(const wchar_t ch)
{
    return ch == TOKEN_LITERALS[1].value[0] || ch == TOKEN_LITERALS[1].value[1];
}

class Lexer
{
    typedef std::shared_ptr<IToken> tokenPointer;

public:
    explicit Lexer(std::wstring code);

    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer()                                 = default;

    std::vector<tokenPointer> lexicalCodeAnalysis();

protected:
    static std::shared_ptr<IToken> createrToken(TokenType token_type,
        const std::wstring& value);

    std::shared_ptr<IToken> test_func_operator();
    std::shared_ptr<IToken> test_func_literal();
    std::shared_ptr<IToken> test_func_data_type();


private:
    static const char SPACE;
    static const std::wstring NOTHING;
    static const size_t       MIN_SIZE_VEC;

    std::wstring _inputCode;
    unsigned int _position;
    std::vector<tokenPointer> _tokens;



};

#endif //TESTLEXER_HPP
