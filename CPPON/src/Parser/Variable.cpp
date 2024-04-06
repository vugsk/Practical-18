
#include "Variable.hpp"

Var::Var(std::wstring   name, std::wstring value, std::wstring type,
         const uint32_t line)
        : _name(std::move(name)), _type_token(std::move(type))
        , _line(line)
{
    if (_type_token == L"число")
    {
        _type_factic = L"int";
        _value = stoi(value);
    }
    else if (_type_token == L"строка")
    {
        _type_factic = L"wstring";
        _value = std::move(value);
    }
    else if (_type_token == L"символ")
    {
        _type_factic = L"wchar_t";
        _value = std::move(value)[1];
    }
}

std::wstring Var::get_name() const
{
    return _name;
}

std::any Var::get_value() const
{
    return _value;
}

std::wstring Var::get_type_token() const
{
    return _type_token;
}

std::wstring Var::get_type_factic() const
{
    return _type_factic;
}

uint32_t Var::get_line() const
{
    return _line;
}

std::vector<uint32_t> Var::get_lines_val() const
{ 
    return std::vector{_line};
}






std::wstring None::get_name() const
{ 
    return L"NONE";
}
std::any     None::get_value() const
{
    return L"NONE";
}
std::wstring None::get_type_token() const
{
    return L"NONE";
}
std::wstring None::get_type_factic() const
{ 
    return L"NONE";
}
uint32_t None::get_line() const
{ 
    return 0;
}
std::vector<uint32_t> None::get_lines_val() const
{
    return {};
}
