
#ifndef TESTLEXER_HPP
#define TESTLEXER_HPP

#ifdef DEBUG_LEXER
    #include <iostream>
#endif

#include <cstdint>
#include <functional>
#include <string>

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
        constexpr void printDebug()
        {
            for (const auto& i : _words)
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

protected:
    constexpr std::wstring addStringLiterale(wchar_t symbol,
        std::wstring&& lexem);

    constexpr std::wstring checkForSeparator(wchar_t symbol,
        std::wstring&& lexeme);

    constexpr void addWord(std::wstring&& lexeme);
    constexpr void parseCode(const std::wstring& code);
    void           mergeStringLiterale();

    template<typename T>
    [[nodiscard]] constexpr T findValueGivenCondition(
        const uint32_t start_index, const uint32_t end_index,
        const std::function<bool(const std::wstring&)>& func)
    {
        for (auto i = start_index; i < end_index; ++i)
            if (func(_words[i]))
                return static_cast<T>(i);
        return T{};
    }

private:
    static constinit const wchar_t* _string;
    static constinit const wchar_t* _default;
    static constinit const wchar_t* _empty_line;

    const wchar_t* _state;
    uint16_t       _tokenIndex;
    uint32_t       _line;
    uint32_t       _position;

    std::vector<std::wstring> _words;
};

#endif //TESTLEXER_HPP
