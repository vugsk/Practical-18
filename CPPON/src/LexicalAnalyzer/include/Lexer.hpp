
#ifndef TESTLEXER_HPP
#define TESTLEXER_HPP


// #define DEBUG_LEXER
// #define TEST_LEXER


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
    void printDebug()
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

        constexpr void parseForTest(const std::wstring& code)
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

    constexpr void test_func_(bool is, std::wstring&& str);
    constexpr void parseCode(const std::wstring& code);
    constexpr void addWord(std::wstring&& lexeme);
    void           mergeStringLiterale();

    template<typename T>
    [[nodiscard]] constexpr T findsValueGivenCondition(
        const uint32_t start_index, const uint32_t end_index,
        const std::function<bool(const std::wstring&)>& func)
    {
        const auto it = std::find_if(
            std::next(_words.begin(), start_index),
            std::next(_words.begin(), end_index), func);

        if (it != std::next(_words.begin(), end_index))
            return static_cast<T>(std::distance(_words.begin(), it));
        return T{};
    }

private:
    static constinit const wchar_t* _string;
    static constinit const wchar_t* _default;
    static constinit const wchar_t* _empty_line;
    static constinit uint32_t       _begin_number;

    const wchar_t* _state;
    uint16_t       _tokenIndex;
    uint32_t       _line;
    uint32_t       _position;

    std::vector<std::wstring> _words;
};




#endif //TESTLEXER_HPP
