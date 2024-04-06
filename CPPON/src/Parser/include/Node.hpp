
#ifndef NODE_HPP
#define NODE_HPP

#include <any>
#include <cstdint>
#include <string>
#include <vector>

class Node
{
public:
    virtual ~Node() = default;
    virtual std::wstring get_name() const = 0;
    virtual std::any get_value() const = 0;
    virtual std::wstring get_type_token() const = 0;
    virtual std::wstring get_type_factic() const = 0;
    virtual uint32_t get_line() const = 0;
    virtual std::vector<uint32_t> get_lines_val() const = 0;
};


#endif //NODE_HPP
