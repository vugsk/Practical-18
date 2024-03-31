
#ifndef NODE_HPP
#define NODE_HPP

#include <any>
#include <cstdint>
#include <string>

class Node
{
public:
    virtual ~Node() = default;
    virtual std::wstring get_name() const = 0;
    virtual std::any get_value() const = 0;
    virtual std::wstring get_type_token() const = 0;
    virtual std::wstring get_type_factic() const = 0;
    virtual u_int32_t get_line() const = 0;
};

class Var final : public Node
{
public:
    Var(std::wstring name, std::wstring value, std::wstring type, uint32_t line);
    ~Var() override = default;

    std::wstring get_name() const override;
    std::any     get_value() const override;
    std::wstring get_type_token() const override;
    std::wstring get_type_factic() const override;
    uint32_t get_line() const override;

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
    Struct(std::wstring name, std::any value, std::wstring type,
        uint32_t line);
    ~Struct() override = default;

    std::wstring get_name() const override;
    std::any     get_value() const override;
    std::wstring get_type_token() const override;
    std::wstring get_type_factic() const override;
    uint32_t get_line() const override;

private:
    std::wstring _name;
    std::any     _value;
    std::wstring _type_token;
    std::wstring _type_factic;
    uint32_t    _line{};
};






#endif //NODE_HPP
