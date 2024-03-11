
#include "Lexer.hpp"

#include <algorithm>

const std::wstring Lexer::NOTHING      = L"NOTHING";
const size_t       Lexer::MIN_SIZE_VEC = 4;


Lexer::Lexer(std::wstring input)
    : _input(std::move(input)) {}

std::vector<Lexer::tokenPtr> Lexer::lexicalCodeAnalysis()
{
    std::vector<tokenPtr> m_tokens;
    for(auto pos = 0; pos < _input.size(); pos++)
    {
        for (const auto& i : test_vec)
        {
            const tokenPtr io = i(pos);
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

bool Lexer::isNullToken(const tokenPtr& token,
    const std::wstring& value_if)
{
    return token->getToken() != null || token->getValue() != value_if;
}

Lexer::tokenPtr Lexer::createNoneToken(const std::wstring& value)
{
    return createToken(none, value);
}

Lexer::tokenPtr Lexer::createNullToken(const std::wstring& value)
{
    return createToken(null, value);
}

Lexer::tokenPtr Lexer::findOperatorAtPosition(const int pos)
{
    return findToken(OPERATORS,
        checkingCharacterMatchesPosition(pos, true),
        createNullToken(NOTHING));
}

Lexer::tokenPtr Lexer::createNumberToken(int& pos)
{
    return createTokenWithExtractedString(pos, number_literal,
        iswdigit, test_func_bind_lamda(iswdigit));
}

Lexer::tokenPtr Lexer::createStringToken(int& pos)
{
    return createTokenWithExtractedString(pos, string_literal,
        IsQuote, [this](int& i)
            { return checkingCharacterMatchesPosition(i++, false); });
}

Lexer::tokenPtr Lexer::createCommandToken(int& pos)
{
    if (iswalpha(_input[pos]))
    {
        const std::wstring io = extractString(pos, iswalnum);
        return findToken<std::wstring>(DATA_TYPES,
            сompareStrings(io), createToken(id, io));
    }
    return createNullToken(NOTHING);
}
