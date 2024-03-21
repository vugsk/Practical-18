
#ifndef TESTLEXER_HPP
#define TESTLEXER_HPP


#define DEBUG_LEXER
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

        void parseForTest(const std::wstring& code)
        {
            if (!_words.empty())
                _words.clear();
            parseCode(code);
            mergeStringLiterale();
        }
    #endif

protected:
    void addStringLiterale(wchar_t symbol, std::wstring& lexem);
    void checkForSeparator(wchar_t symbol, std::wstring& lexeme);
    void parseCode(const std::wstring& code);
    void mergeStringLiterale();

    constexpr std::wstring functionAddsWordsOnCondition(bool condition,
        const std::wstring& lexeme);

    [[nodiscard]] constexpr std::wstring glueWordsTogether(uint32_t start_index,
        uint32_t end_index) const;

    constexpr std::wstring addWord(const std::wstring& lexeme);

    template<typename T>
    [[nodiscard]] constexpr T findsValueGivenCondition(
        const uint32_t start_index, const uint32_t end_index,
        const std::function<bool(const std::wstring&)>& func)
    {
        for (auto i = start_index; i < end_index; ++i)
            if (func(_words[i]))
                return i;
        return 0;
    }

private:
    static constexpr const wchar_t* STRING = L"IN_STRING";
    static constexpr const wchar_t* DEFAULT = L"DEFAULT";

    const wchar_t* _state;
    uint16_t _tokenIndex;
    uint32_t _line;
    uint32_t _position;

    std::vector<std::wstring> _words;

};

#endif //TESTLEXER_HPP
