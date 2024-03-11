
#include "Lexer.hpp"

#include <algorithm>

const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;


Lexer::Lexer(std::wstring input) : _input(std::move(input)) {}

std::vector<Lexer::tokenPointer> Lexer::lexicalCodeAnalysis()
{
    std::vector<tokenPointer> m_tokens;
    for(auto pos = 0; pos < _input.size(); pos++)
    {
        for (const auto& i : _tokenMakers)
        {
            const tokenPointer io = i(pos);
            if (isNullToken(io, NOTHING))
                m_tokens.push_back(io);
        }
    }

    m_tokens.push_back(createToken(end, END));
    return m_tokens;
}

Lexer::funcBoolWcharT Lexer::checkingCharacterMatchesPosition(int pos, bool is)
const {
    return [this, pos, is](const wchar_t i) -> bool
    {
        return is ? _input[pos] == i : _input[pos] != i;
    };
}

std::function<bool(const std::wstring&)> Lexer::сompareStrings(
    const std::wstring& sb)
{
    return [sb](const std::wstring& i) -> bool
    {
        return std::ranges::equal(sb, i);
    };
}

std::wstring Lexer::extractString(int& position,
    const funcBoolWcharT& func) const
{
    std::wstring sb;
    while (func(_input[position]))
        sb.push_back(_input[position++]);
    return sb;
}

bool Lexer::isNullToken(const tokenPointer& token,
    const std::wstring& value_if)
{
    return token->getToken() != null || token->getValue() != value_if;
}

Lexer::tokenPointer Lexer::createNoneToken(const std::wstring& value)
{
    return createToken(none, value);
}

Lexer::tokenPointer Lexer::createNullToken(const std::wstring& value)
{
    return createToken(null, value);
}

Lexer::tokenPointer Lexer::findOperatorAtPosition(const int pos)
{
    return findToken(OPERATORS,
        checkingCharacterMatchesPosition(pos, true),
        createNullToken(NOTHING));
}

Lexer::tokenPointer Lexer::createNumberToken(int& pos)
{
    return createTokenWithExtractedString(pos, number_literal,
        iswdigit, test_func_bind_lamda(iswdigit));
}

Lexer::tokenPointer Lexer::createStringToken(int& pos)
{
    return createTokenWithExtractedString(pos, string_literal,
        IsQuote, [this](int& i)
            { return checkingCharacterMatchesPosition(i++, false); });
}

Lexer::tokenPointer Lexer::createCommandToken(int& pos)
{
    if (iswalpha(_input[pos]))
    {
        const std::wstring io = extractString(pos, iswalnum);
        return findToken<std::wstring>(DATA_TYPES,
            сompareStrings(io), createToken(id, io));
    }
    return createNullToken(NOTHING);
}
