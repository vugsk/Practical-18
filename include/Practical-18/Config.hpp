
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>

#define TEST false
#define DEBUG false

enum class TokenType
{
    COLON,          // двоеточие
    SEMICOLON,      // точка с запятой
    ASSIGNMENT,     // присваиваивание


    STRING_LITERAL, // кавычки
    NUMBER_LITERAL,


    NUMBER_DATATYPE,
    STRING_DATATYPE,
    CHARACTER_DATATYPE,
    ID,


    END,
};

class Token
{
public:
    Token(const TokenType token, std::wstring value)
        : _token(token), _value(std::move(value)) {}

    [[nodiscard]] TokenType getToken() const
    {
        return _token;
    }

    [[nodiscard]] std::wstring getValue() const
    {
        return _value;
    }

private:
    TokenType _token;
    std::wstring _value;
};

constexpr wchar_t      COLON          = ':';
constexpr wchar_t      SEMICOLON      = ';';
constexpr wchar_t      ASSIGNMENT     = '=';
constexpr wchar_t      SPACE          = ' ';
constexpr wchar_t      ENTER          = '\n';
constexpr std::wstring END            = L"NUL";
constexpr std::pair    STRING_LITERAL = {L'\"', L'\''};
const std::wstring     NUMBER         = L"число";
const std::wstring     STRING         = L"строка";
const std::wstring     CHARACTER      = L"символ";


const std::vector<std::pair<TokenType, wchar_t>> TYPE_CHAR_
{
    {TokenType::COLON, COLON},
    {TokenType::SEMICOLON, SEMICOLON},
    {TokenType::ASSIGNMENT, ASSIGNMENT},
};

const std::vector<std::pair<TokenType, std::wstring>> TYPE_DATA_
{
    {TokenType::NUMBER_DATATYPE, NUMBER},
    {TokenType::STRING_DATATYPE, STRING},
    {TokenType::CHARACTER_DATATYPE, CHARACTER},
};



[[nodiscard]] bool IsDigit(wchar_t number);
[[nodiscard]] bool IsSpace(wchar_t _ch);
[[nodiscard]] bool IsSymbol(wchar_t _ch);
[[nodiscard]] bool IsLetterOrDigit(wchar_t _ch);
[[nodiscard]] bool is_func(wchar_t ch);
[[nodiscard]] bool isEnter(wchar_t ch);
[[nodiscard]] bool isQuote(wchar_t ch);
[[nodiscard]] bool is_func_E_Q_S(wchar_t ch);
[[nodiscard]] bool test_func_bool(wchar_t ch, wchar_t i, bool is);

[[nodiscard]] std::wstring ConvertString(const std::string& string);

[[nodiscard]] std::wstring test_st(const std::wstring& _input, int& position,
    const std::function<bool(wchar_t)>& func);

template<typename T>
[[nodiscard]] std::wstring test_func_wstring(const T& t)
{
    std::wstring io;
    io = t;
    return io;
}

template<typename T>
[[nodiscard]] std::pair<bool, std::shared_ptr<Token>> test_func_(
    const std::vector<std::pair<TokenType, T>>& vec,
    const std::function<bool(const T&)>& func)
{
    for (const auto& [_token, ch] : vec)
        if (func(ch))
            return {true, make_shared<Token>(_token, test_func_wstring(ch))};
    return {false, nullptr};
}

#endif //CONFIG_HPP
