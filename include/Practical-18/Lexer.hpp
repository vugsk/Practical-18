#ifndef LEXER_HPP
#define LEXER_HPP

#include <algorithm>
#include <functional>
#include <utility>


#include "ILexer.hpp"
#include "Token.hpp"

class Lexer final : public ILexer
{
public:
    explicit Lexer(std::wstring input_text)
        : m_input(std::move(input_text)), m_position(0) {}
    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer()                                 override = default;

    std::vector<std::shared_ptr<IToken>> test_func() override;

protected:
    std::wstring test_func_wstring_(const std::function<bool(wchar_t)>& func);

    std::shared_ptr<IToken> identifierOrKeyword();

    template<typename T>
    [[nodiscard]] std::pair<bool, std::shared_ptr<IToken>> test_func_(
        const std::vector<std::pair<TokenType, T>>& vec,
        const std::function<bool(const T&)>& func)
    {
        for (const auto& [_token, ch] : vec)
            if (func(ch))
                return {true, make_shared<Token>(_token, test_func_wstring(ch))};
        return {false, nullptr};
    }

private:
    std::wstring                         m_input;
    int                                  m_position;
    std::vector<std::shared_ptr<IToken>> m_token;
};

#endif //LEXER_HPP
