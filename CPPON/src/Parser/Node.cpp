
#include "Node.hpp"
#include "IToken.hpp"

#include <any>
#include <memory>
#include <utility>
#include <vector>

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










Struct::Struct(std::wstring name, std::vector<std::shared_ptr<IToken>> value,
    std::wstring type, uint32_t line)
        : _name(std::move(name)), _type_token(std::move(type))
        , _line(line)
{
    _type_factic = _name;

    std::vector<std::shared_ptr<Node>> var;
    std::vector<std::shared_ptr<IToken>> line_token;
    
    for (auto i : value)
    {
        if (i->getValue() == L",")
        {
            var.push_back(std::make_shared<Var>(line_token[0]->getValue(), 
                                                  line_token[4]->getValue(), 
                                                  line_token[2]->getValue(), 
                                                  line_token[0]->getLine()));
            
            _lines.push_back(line_token.front()->getLine());

            line_token.clear();
            continue;
        }
        line_token.push_back(i);
    }

    _value = var;

}

std::wstring Struct::get_name() const
{
    return _name;
}

std::any Struct::get_value() const
{
    return _value;
}

std::wstring Struct::get_type_token() const
{
    return _type_token;
}

std::wstring Struct::get_type_factic() const
{
    return _type_factic;
}

uint32_t Struct::get_line() const
{
    return _line;
}

std::vector<uint32_t> Struct::get_lines_val() const
{
    return _lines;
}

