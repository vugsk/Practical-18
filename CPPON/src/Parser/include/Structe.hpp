
#ifndef STRUCTE_HPP
#define STRUCTE_HPP

#include "IToken.hpp"
#include "Node.hpp"

#include <memory>


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


#endif //STRUCTE_HPP