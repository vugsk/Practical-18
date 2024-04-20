
#include "cppon.hpp"

Test_array::Test_array(const std::vector<std::shared_ptr<Node>>& list)
{
    _arr = list;
}
Test_array::Test_array(const Test_array& other)
{
    _arr = other._arr;
}
