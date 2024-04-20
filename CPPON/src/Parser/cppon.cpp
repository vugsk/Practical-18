
#include "cppon.hpp"

CppOn::CppOn(const std::vector<std::shared_ptr<Node>>& list)
{
    _arr = list;
}
CppOn::CppOn(const CppOn& other)
{
    _arr = other._arr;
}
