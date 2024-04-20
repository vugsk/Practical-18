
#ifndef CPPON_HPP
#define CPPON_HPP

#include "Node.hpp"

#include <memory>

class Test_array
{
public:
    Test_array() = default;
    Test_array(const std::vector<std::shared_ptr<Node>>& list);
    Test_array(const Test_array& other);

    template<typename T1>
    T1 getVal(const std::wstring& key)
    {
        for (auto i : _arr)
            if (i->get_name() == key)
                return std::any_cast<T1>(i->get_value());
        return T1{};
    }

private:
    std::vector<std::shared_ptr<Node>> _arr;
};

#endif