
#ifndef TESTLEXER_HPP
#define TESTLEXER_HPP


#ifdef DEBUG_LEXER
    #include <iostream>
#endif

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class IToken;

class Lexer
{
public:
    #ifdef TEST_LEXER
        Lexer() = default;
    #endif

    explicit Lexer(const std::wstring& code);

    Lexer(const Lexer& other)                = delete;
    Lexer(Lexer&& other) noexcept            = delete;
    Lexer& operator=(const Lexer& other)     = delete;
    Lexer& operator=(Lexer&& other) noexcept = delete;
    ~Lexer()                                 = default;

    #ifdef DEBUG_LEXER
        static constexpr void printDebug()
        {
            for (const auto i : _words)
                std::wcout << i << '\n';
        }
    #endif
    #ifdef TEST_LEXER
        [[nodiscard]] constexpr std::vector<std::wstring> getWords()
        {
            return _words;
        }

        void parseForTest(const std::wstring& code)
        {
            if (!_words.empty())
                _words.clear();
            parseCode(code);
            mergeStringLiterale();
        }
    #endif

    [[nodiscard]] static std::vector<std::shared_ptr<IToken>> test_func();

protected:
    constexpr std::wstring addStringLiterale(wchar_t symbol,
        std::wstring&& lexem);

    constexpr std::wstring checkForSeparator(wchar_t symbol,
        std::wstring&& lexeme);

    constexpr void addWord(std::wstring&& lexeme);
    constexpr void parseCode(const std::wstring& code);
    constexpr void mergeStringLiterale() const;

    template<typename T, typename F>
    [[nodiscard]] static constexpr T findValueGivenCondition(F&& func,
        const std::pair<uint32_t, uint32_t>& range =
            {0, static_cast<uint32_t>(_words.size())})
    {
        for (auto i = range.first; i < range.second; ++i)
            if (func(_words[i]))
                return static_cast<T>(i);
        return T{};
    }

private:
    static constinit const wchar_t*                       _string;
    static constinit const wchar_t*                       _default;
    static constinit const wchar_t*                       _empty_line;
    static constinit std::vector<std::wstring>            _words;
    static constinit std::vector<std::shared_ptr<IToken>> _tokens;

    const wchar_t* _state;
    uint16_t       _tokenIndex;
    uint32_t       _line;
    uint32_t       _position;
};

#endif //TESTLEXER_HPP
