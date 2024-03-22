
#include "Lexer.hpp"

#include <algorithm>

using std::wstring;
using std::move;

constinit const wchar_t* Lexer::_string       = L"IN_STRING";
constinit const wchar_t* Lexer::_default      = L"DEFAULT";
constinit const wchar_t* Lexer::_empty_line   = L"";
constinit uint32_t       Lexer::_begin_number = 0;


[[nodiscard]] static constexpr bool IsDoubleQuote(const wchar_t ch)
{
    return ch == '\"';
}
[[nodiscard]] static constexpr bool IsQuote(const wchar_t ch)
{
    return IsDoubleQuote(ch) || ch == '\'';
}
[[nodiscard]] static constexpr bool IsSpace(const wchar_t ch)
{
    return ch == ' ';
}
[[nodiscard]] static constexpr bool IsEnter(const wchar_t ch)
{
    return ch == '\n';
}
[[nodiscard]] static constexpr bool IsSeparators(const wchar_t ch)
{
    return !IsSpace(ch) && ch != '\r' && !IsEnter(ch);
}
[[nodiscard]] static constexpr bool IsSeparateSymbol(const wchar_t symbol)
{
    return  symbol == ':'   || symbol == ';' ||
            symbol == ','   || symbol == '(' ||
            symbol == ')'   || symbol == '[' ||
            symbol == ']'   || symbol == '=' ||
            IsSpace(symbol)|| symbol == '\r'||
            IsEnter(symbol)|| symbol == '#';
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
[[nodiscard]] static constexpr wstring sum(const wstring& val_1,
    const wstring& val_2)
{
    return IsSpace(val_2.front()) ? val_2 + val_1 : val_1 + L" " + val_2;
}




Lexer::Lexer(const wstring& code)
    : _state(_default), _tokenIndex(0)
    , _line(0), _position(0)
{
    parseCode(code);
    mergeStringLiterale();
}

constexpr void Lexer::test_func_(const bool is, wstring&& str)
{
    if (is) addWord(move(str));
}

constexpr wstring Lexer::checkForSeparator(const wchar_t symbol,
    wstring&& lexeme)
{
    if (IsSeparateSymbol(symbol))
    {
        test_func_(!lexeme.empty(), move(lexeme));
        test_func_(IsSeparators(symbol), wstring(1, symbol));
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

void Lexer::mergeStringLiterale()
{
    std::pair indexs = std::make_pair(
        findsValueGivenCondition<uint32_t>(_begin_number,
            _words.size(), IsFrontDoubleQuoteStrring),
        findsValueGivenCondition<uint32_t>(_begin_number,
            _words.size(), IsBackDoubleQuoteStrring));

    if (indexs.first == indexs.second)
        return;

    _words.insert(std::next(_words.begin(), indexs.first),
        sum(_words[indexs.first], _words[indexs.second]));

    erase_if(_words, [this, indexs](const wstring& str)
    {
        return findsValueGivenCondition<bool>(indexs.first + 1,
            indexs.second + 2, [str](const wstring& string)
                { return string == str; });
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
            _position = _begin_number;
        }

        current_lexeme = checkForSeparator(symbol, move(current_lexeme));
        current_lexeme = addStringLiterale(symbol, move(current_lexeme));
    }
}
