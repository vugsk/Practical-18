
#include "Lexer.hpp"

#include "Config.hpp"



std::vector<std::shared_ptr<IToken>> Lexer::test_func()
{
    for(m_position = 0; m_position < m_input.size(); m_position++)
    {
        if (is_func(m_input[m_position]))
            m_token.push_back(std::make_shared<Token>(TokenType::STRING_LITERAL,
                test_func_wstring_(test_bind(m_input[m_position++], false))));

        if (IsDigit(m_input[m_position]))
            m_token.push_back(std::make_shared<Token>(TokenType::NUMBER_LITERAL,
                test_func_wstring_(IsDigit)));

        if (IsSymbol(m_input[m_position]))
            m_token.push_back(identifierOrKeyword());

        if (test_func_(TYPE_CHAR_, test_bind(m_input[m_position], true)).first)
            m_token.push_back(test_func_(TYPE_CHAR_, test_bind(m_input[m_position], true)).second);
    }

    m_token.push_back(make_shared<Token>(TokenType::END, END));
    return m_token;
}




std::wstring Lexer::test_func_wstring_(const std::function<bool(wchar_t)>& func)
{
    return test_st(m_input, m_position, func);
}

std::shared_ptr<IToken> Lexer::identifierOrKeyword()
{
    const std::wstring sb = test_st(m_input, m_position, IsLetterOrDigit);
    if (test_func_<std::wstring>(TYPE_DATA_, bind(std::ranges::equal, sb, std::placeholders::_1)).first)
        return test_func_<std::wstring>(TYPE_DATA_, bind(std::ranges::equal, sb, std::placeholders::_1)).second;
    return make_shared<Token>(TokenType::ID, sb);
}
