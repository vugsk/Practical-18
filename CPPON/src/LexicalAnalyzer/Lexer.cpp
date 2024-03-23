
#include "Lexer.hpp"

#include "ConfigLexer.hpp"

#include <algorithm>
#include <cwctype>
#include <Token.hpp>

using std::wstring;
using std::move;
using std::pair;

constinit const wchar_t* Lexer::_string       = L"IN_STRING";
constinit const wchar_t* Lexer::_default      = L"DEFAULT";
constinit const wchar_t* Lexer::_empty_line   = L"";
constinit std::vector<wstring> Lexer::_words{};
constinit std::vector<std::shared_ptr<IToken>>  Lexer::_tokens{};

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
    , _line(0), _position(0)
{
    parseCode(code);
    mergeStringLiterale();
}

std::vector<std::shared_ptr<IToken>> Lexer::test_func()
{
    for (auto i : _words)
        _tokens.push_back(make_shared<Token>(i));
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
    _words.push_back(lexeme);
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
        CombineWithSpaceIfNeeded(move(_words[indexs.first]),
            move(_words[indexs.second])));

    erase_if(_words, [this, indexs](const wstring& str)
    {
        return findValueGivenCondition<bool>(
            [str](const wstring& string){ return string == str; },
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
        {
            ++_line;
            _position = 0;
        }

        current_lexeme = checkForSeparator(symbol, move(current_lexeme));
        current_lexeme = addStringLiterale(symbol, move(current_lexeme));
    }
}
