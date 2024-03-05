// #ifndef LEXER_HPP
// #define LEXER_HPP
//
// #include <algorithm>
// #include <functional>
// #include <TokenType.hpp>
// #include <utility>
//
// #include "ILexer.hpp"
//
// class Lexer final : public ILexer
// {
// public:
//     explicit Lexer(std::wstring input_text)
//         : m_input(std::move(input_text)), m_position(0) {}
//
//     Lexer(const Lexer& other)                = delete;
//     Lexer(Lexer&& other) noexcept            = delete;
//     Lexer& operator=(const Lexer& other)     = delete;
//     Lexer& operator=(Lexer&& other) noexcept = delete;
//     ~Lexer() override                        = default;
//
//     std::vector<std::shared_ptr<IToken>> test_func() override;
//
// protected:
//     std::wstring test_func_wstring_(const std::function<bool(wchar_t)>& func);
//
//     std::shared_ptr<IToken> identifierOrKeyword();
//
//     void test_func_string_leteral();
//     void test_func_number_literal();
//     void test_func_command();
//     void test_func_operator();
//
// private:
//     std::wstring                         m_input;
//     int                                  m_position;
//     std::vector<std::shared_ptr<IToken>> m_token;
// };
//
// #endif //LEXER_HPP
