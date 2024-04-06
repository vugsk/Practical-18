
#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Node.hpp"

class None : public Node
{
public:
    None() = default;
    ~None() = default;

    std::wstring get_name() const override;
    std::any     get_value() const override;
    std::wstring get_type_token() const override;
    std::wstring get_type_factic() const override;
    uint32_t get_line() const override;
    std::vector<uint32_t> get_lines_val() const override;

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
    std::vector<uint32_t> get_lines_val() const override;

private:
    std::wstring _name;
    std::any     _value;
    std::wstring _type_token;
    std::wstring _type_factic;
    uint32_t    _line{};
};


#endif //VARIABLE_HPP