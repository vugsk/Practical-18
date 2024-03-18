
#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>
#include <memory>
#include <Node.hpp>
#include <stack>
#include <unordered_map>
#include <vector>

class IToken;

struct StartPointer
{
    std::wstring name;
    std::unordered_map<std::wstring, std::pair<std::wstring,
        std::variant<int, wchar_t, std::wstring>>> root;
};

class Parser
{
public:
    Parser();

    StartPointer parse(const std::vector<std::shared_ptr<IToken>>& tokens);

protected:
private:
    StartPointer _root;
};


#endif //PARSER_HPP
