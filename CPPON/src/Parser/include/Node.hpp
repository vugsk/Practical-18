
#ifndef NODE_HPP
#define NODE_HPP

#include <algorithm>
#include <string>
#include <variant>

struct Node
{
    std::shared_ptr<Node> right = nullptr;
    std::shared_ptr<Node> left = nullptr;
    std::wstring id;
    std::wstring type;

    template<typename T>
    T value() { return std::get<T>(_value); }

    template<typename T>
    void value(const T& data) { return _value = data; }

private:
    std::variant<int, char, std::wstring> _value;
};









#endif //NODE_HPP
