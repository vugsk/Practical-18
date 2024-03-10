
#include "Vocabulary.hpp"

bool IsQuote(const wchar_t ch)
{
    return ch == CHARACTER_LITERAL || ch == STRING_LITERAL;
}