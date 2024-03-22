
#include "Lexer.hpp"

#include <algorithm>


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
    const std::wstring& str)
{
    return IsDoubleQuote(str.front());
}
[[nodiscard]] static constexpr bool IsBackDoubleQuoteStrring(
    const std::wstring& str)
{
    return IsDoubleQuote(str.back());
}




Lexer::Lexer(const std::wstring& code)
    : _state(_default), _tokenIndex(0)
    , _line(0), _position(0)
{
    parseCode(code);
    mergeStringLiterale();
}

constexpr void Lexer::test_func_(const bool is, const std::wstring&& str)
{
    if (is) addWord(str);
}

constexpr std::wstring Lexer::checkForSeparator(const wchar_t      symbol,
                                                const std::wstring& lexeme)
{
    if (IsSeparateSymbol(symbol))
    {
        test_func_(!lexeme.empty(), std::move(lexeme));
        test_func_(IsSeparators(symbol), std::wstring(1, symbol));
    }
    else
        return lexeme + symbol;
    return L"";
}

constexpr std::wstring Lexer::addStringLiterale(const wchar_t symbol,
                                                const std::wstring& lexem)
{
    if (IsQuote(symbol))
    {
        if (_state == _default)
            _state = _string;
        else if (_state == _string)
        {
            _state = _default;
            addWord(lexem);
            return L"";
        }
    }
    return lexem;
}

constexpr void Lexer::addWord(const std::wstring& lexeme)
{
    _words.push_back(lexeme);
    ++_tokenIndex;
}

constexpr std::wstring Lexer::glueWordsTogether(const uint32_t start_index,
    const uint32_t end_index) const
{
    if (IsSpace(_words[end_index].front()))
        return _words[start_index] + _words[end_index];
    return _words[start_index] + L" " + _words[end_index];
}

void Lexer::mergeStringLiterale()
{
    uint32_t start_index = findsValueGivenCondition<uint32_t>(
        _begin_number, _words.size(),
        IsFrontDoubleQuoteStrring);

    uint32_t end_index = findsValueGivenCondition<uint32_t>(
        _begin_number, _words.size(),
        IsBackDoubleQuoteStrring);

    if (start_index == end_index)
        return;

    _words.insert(_words.begin() + start_index,
        glueWordsTogether(start_index, end_index));

    erase_if(_words,
        [this, start_index, end_index](const std::wstring& str)
    {
        return findsValueGivenCondition<bool>(start_index + 1,
            end_index + 2, [str](const std::wstring& string)
                { return string == str; });
    });
}

constexpr void Lexer::parseCode(const std::wstring& code)
{
    _tokenIndex = -1;
    std::wstring current_lexeme;
    for (const auto& symbol : code)
    {
        if (IsEnter(symbol))
        {
            ++_line;
            _position = _begin_number;
        }

        current_lexeme = checkForSeparator(symbol, current_lexeme);
        current_lexeme = addStringLiterale(symbol, current_lexeme);
    }
}
