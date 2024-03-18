
#include "Parser.hpp"

#include <IToken.hpp>
#include <TypeToken.hpp>
#include <unordered_map>

Parser::Parser() = default;

// * операторы действия -> =
// * оператор определения типа -> :
// * оператор конца строки -> ;

StartPointer Parser::parse(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    std::shared_ptr<Node> temp = nullptr;
    std::unordered_map<std::wstring, std::pair<std::wstring,
        std::variant<int, wchar_t, std::wstring>>> temp_test;

    std::wstring name_var;

    for (auto i = 0; i < tokens.size(); i++)
    {
        if (tokens[i]->getToken() == id)
        {
            name_var = tokens[i]->getValue();
            temp_test[tokens[i]->getValue()];
        }
        else if (tokens[i]->getToken() == number_datatype)
        {
            temp_test[name_var].first = tokens[i]->getValue();
        }
        else if (tokens[i]->getToken() == string_datatype)
        {
            temp_test[name_var].first = tokens[i]->getValue();
        }
        else if (tokens[i]->getToken() == character_datatype)
        {
            temp_test[name_var].first = tokens[i]->getValue();
        }
        else if (tokens[i]->getToken() == number_literal)
        {
            temp_test[name_var].second = stoi(tokens[i]->getValue());
        }
        else if (tokens[i]->getToken() == string_literal)
        {
            if (tokens[i]->getValue().size() == 1)
                temp_test[name_var].second = tokens[i]->getValue()[0];
            else
                temp_test[name_var].second = tokens[i]->getValue();
        }
    }

    _root.root = temp_test;

    return _root;
}
