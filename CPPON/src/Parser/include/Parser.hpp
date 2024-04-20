
#ifndef PARSER_HPP
#define PARSER_HPP

// #define PARSER_DEBUG

#include <any>

#ifdef PARSER_DEBUG
    #include <iostream>
#endif

#include "cppon.hpp"
#include "IToken.hpp"


class Parser
{
public:
    explicit Parser(const std::vector<std::shared_ptr<IToken>>& tokens);

    Parser(const Parser& other)                = delete;
    Parser(Parser&& other) noexcept            = delete;
    Parser& operator=(const Parser& other)     = delete;
    Parser& operator=(Parser&& other) noexcept = delete;
    ~Parser()                                  = default;

    template<typename T>
    constexpr T GetValueByKey(const std::wstring& key) const
    {
        for (const auto& i : _nodes)
        {
            if (i->get_name() == key &&
                i->get_type_token() != L"структура")
            {
                return std::any_cast<T>(i->get_value());
            }
        }
        return T{};
    }

    uint32_t getSize()
    {
        int count = 0;
        for (const auto& i : _nodes)
            if (i->get_type_token() == L"структура")
                count++;
        return count;
    }

    CppOn getStructureByKey(const std::wstring& key) const;

    #ifdef PARSER_DEBUG
        void printDebug() const
        {
            for (const auto& node : _nodes)
            {
                std::wcout << node->get_name() << ' '
                            << node->get_type_token() << ' '
                            << node->get_type_factic() << ' '
                            << node->get_line() << ' '
                            << node->get_value().type().name() << '\n';
            }
        }
    #endif

protected:
    constexpr void parse(const std::vector<std::shared_ptr<IToken>>& tokens);
    void checkTokens(const std::vector<std::shared_ptr<IToken>>& tokens);

private:
    std::vector<std::shared_ptr<Node>> _nodes;
};


#endif //PARSER_HPP
