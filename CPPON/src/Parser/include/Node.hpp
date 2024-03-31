
#ifndef NODE_HPP
#define NODE_HPP

#include "IToken.hpp"
#include <any>
#include <cstdint>
#include <memory>
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

class Var : public Node
{
public:
    Var(std::wstring name, std::wstring value, std::wstring type, uint32_t line);
    ~Var() override = default;

    std::wstring get_name() const override;
    std::any     get_value() const override;
    std::wstring get_type_token() const override;
    std::wstring get_type_factic() const override;
    uint32_t get_line() const override;
    std::vector<uint32_t> get_lines_val() const override = 0;

private:
    std::wstring _name;
    std::any     _value;
    std::wstring _type_token;
    std::wstring _type_factic;
    uint32_t    _line{};
};




class Struct final : public Node
{
public:
    Struct(std::wstring name, std::vector<std::shared_ptr<IToken>> value, 
        std::wstring type, uint32_t line);
    ~Struct() override = default;

    std::wstring get_name() const override;
    std::any     get_value() const override;
    std::wstring get_type_token() const override;
    std::wstring get_type_factic() const override;
    uint32_t get_line() const override;
    std::vector<uint32_t> get_lines_val() const override;

private:
    std::wstring _name;
    std::any     _value;
    std::wstring _type_token;
    std::wstring _type_factic;
    uint32_t     _line{};
    std::vector<uint32_t> _lines;
};






#endif //NODE_HPP
