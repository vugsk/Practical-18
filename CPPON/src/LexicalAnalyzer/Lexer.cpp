
#include "Lexer.hpp"

#include "ConfigLexer.hpp"
#include "Token.hpp"

#include <algorithm>
#include <cwctype>

using std::wstring;
using std::move;
using std::pair;
using std::shared_ptr;
using std::vector;

constinit const wchar_t* Lexer::_string       = L"IN_STRING";
constinit const wchar_t* Lexer::_default      = L"DEFAULT";
constinit const wchar_t* Lexer::_end          = L"END";
constinit const wchar_t* Lexer::_empty_line   = L"";
constinit vector<pair<wstring, uint32_t>> Lexer::_words{};
constinit vector<shared_ptr<IToken>>  Lexer::_tokens{};



[[nodiscard]] static constexpr bool IsQuote(const wchar_t ch)
{
    return IsDoubleQuote(ch) || ch == '\'';
}
[[nodiscard]] static constexpr bool IsEnter(const wchar_t ch)
{
    return ch == '\n';
}
[[nodiscard]] static constexpr bool IsSeparators(const wchar_t ch)
{
    return !iswspace(ch) && ch != '\r' && !IsEnter(ch);
}
[[nodiscard]] static constexpr bool IsSeparateSymbol(const wchar_t symbol)
{
    return  symbol == ':'   || symbol == ';' ||
            symbol == ','   || symbol == '(' ||
            symbol == ')'   || symbol == '[' ||
            symbol == ']'   || symbol == '=' ||
            iswspace(symbol)|| symbol == '\r'||
            IsEnter(symbol) || symbol == '#';
}
[[nodiscard]] static constexpr bool IsFrontDoubleQuoteStrring(
    const wstring& str)
{
    return IsDoubleQuote(str.front());
}
[[nodiscard]] static constexpr bool IsBackDoubleQuoteStrring(const wstring& str)
{
    return IsDoubleQuote(str.back());
}

[[nodiscard]] static constexpr wstring CombineWithSpaceIfNeeded(
    wstring&& val_1, wstring&& val_2)
{
    return iswspace(val_2.front()) ? val_2 + val_1 : val_1 + L" " + val_2;
}

template<typename T>
[[nodiscard]] static constexpr pair<T, T> test_f(const pair<T, T>& pair_t,
    T&& val_1, T&& val_2)
{
    return std::make_pair(pair_t.first + val_1, pair_t.second + val_2);
}




Lexer::Lexer(const wstring& code)
    : _state(_default), _tokenIndex(0)
    , _line(1)
{
    parseCode(code);
    mergeStringLiterale();
}

std::vector<shared_ptr<IToken>> Lexer::test_func()
{
    for (const auto& [value, line] : _words)
        _tokens.push_back(std::make_shared<Token>(value, line));
    return _tokens;
}

constexpr wstring Lexer::checkForSeparator(const wchar_t symbol,
                                           wstring&& lexeme)
{
    if (IsSeparateSymbol(symbol))
    {
        if (!lexeme.empty())
            addWord(move(lexeme));
        if (IsSeparators(symbol))
            addWord(wstring(1, symbol));
    }
    else
        return lexeme + symbol;
    return _empty_line;
}

constexpr wstring Lexer::addStringLiterale(const wchar_t symbol,
    wstring&& lexem)
{
    if (IsQuote(symbol))
    {
        if (_state == _default)
            _state = _string;
        else if (_state == _string)
        {
            _state = _default;
            addWord(move(lexem));
            return _empty_line;
        }
    }
    return lexem;
}

constexpr void Lexer::addWord(wstring&& lexeme)
{
    _words.emplace_back(lexeme, _line);
    ++_tokenIndex;
}

constexpr void Lexer::mergeStringLiterale() const
{
    pair indexs = std::make_pair(
        findValueGivenCondition<uint32_t>(IsFrontDoubleQuoteStrring),
        findValueGivenCondition<uint32_t>(IsBackDoubleQuoteStrring));

    if (indexs.first == indexs.second)
        return;

    _words.insert(next(_words.begin(), indexs.first),
        std::make_pair(CombineWithSpaceIfNeeded(
            move(_words[indexs.first].first), move(_words[indexs.second].first)),
            _words[indexs.first].second));

    erase_if(_words,
        [this, indexs](const pair<std::wstring, uint32_t>& str)
    {
        return findValueGivenCondition<bool>(
            [str](const wstring& string){ return string == str.first; },
            test_f<uint32_t>(indexs, 1, 2));
    });
}

constexpr void Lexer::parseCode(const wstring& code)
{
    _tokenIndex = -1;
    wstring current_lexeme;
    for (const auto& symbol : code)
    {
        if (IsEnter(symbol))
            ++_line;

        current_lexeme = checkForSeparator(symbol, move(current_lexeme));
        current_lexeme = addStringLiterale(symbol, move(current_lexeme));
    }
}
