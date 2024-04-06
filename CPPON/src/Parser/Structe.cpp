
#include "Structe.hpp"

#include "Token.hpp"
#include "Variable.hpp"

#include <memory>

Struct::Struct(std::wstring name, std::vector<std::shared_ptr<IToken>> value,
    std::wstring type, uint32_t line)
        : _name(std::move(name)), _type_token(std::move(type))
        , _line(line)
{
    _type_factic = _name;

    std::vector<std::shared_ptr<Node>> var;
    std::vector<std::shared_ptr<IToken>> line_token;
    
    if (value.back()->getValue() != L",")
        value.push_back(std::make_shared<Token>(L",", value.back()->getLine()));

    for (const auto& i : value)
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
