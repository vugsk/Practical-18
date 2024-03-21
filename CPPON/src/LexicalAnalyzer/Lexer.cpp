
#include "Lexer.hpp"


static constexpr uint32_t       BEGIN_NUMBER = 0;
static constexpr const wchar_t* EMPTY_LINE   = L"";


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
    : _state(DEFAULT), _tokenIndex(0)
    , _line(0), _position(0)
{
    parseCode(code);
    mergeStringLiterale();
}


void Lexer::checkForSeparator(const wchar_t symbol, std::wstring& lexeme)
{
    if (IsSeparateSymbol(symbol))
    {
        lexeme = functionAddsWordsOnCondition(!lexeme.empty(), lexeme);
        functionAddsWordsOnCondition(IsSeparators(symbol),
            std::wstring(1, symbol));
    }
    else
        lexeme += symbol;
}

constexpr std::wstring Lexer::functionAddsWordsOnCondition(const bool condition,
    const std::wstring& lexeme)
{
    return condition ? addWord(lexeme) : EMPTY_LINE;
}

void Lexer::addStringLiterale(const wchar_t symbol,
    std::wstring& lexem)
{
    if (IsQuote(symbol))
    {
        if (_state == DEFAULT)
            _state = STRING;
        else if (_state == STRING)
        {
            _state = DEFAULT;
            addWord(lexem);
            lexem.clear();
        }
    }
}

constexpr std::wstring Lexer::addWord(const std::wstring& lexeme)
{
    _words.push_back(lexeme);
    ++_tokenIndex;
    return EMPTY_LINE;
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
        BEGIN_NUMBER, _words.size(),
        IsFrontDoubleQuoteStrring);

    uint32_t end_index = findsValueGivenCondition<uint32_t>(
        BEGIN_NUMBER, _words.size(),
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

void Lexer::parseCode(const std::wstring& code)
{
    _tokenIndex = -1;
    std::wstring current_lexeme;
    for (const auto& symbol : code)
    {
        if (IsEnter(symbol))
        {
            ++_line;
            _position = BEGIN_NUMBER;
        }

        checkForSeparator(symbol, current_lexeme);
        addStringLiterale(symbol, current_lexeme);
    }
}


