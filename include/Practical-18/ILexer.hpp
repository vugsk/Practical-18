
#ifndef ILEXER_HPP
#define ILEXER_HPP

#include <memory>
#include <vector>

#include "IToken.hpp"

namespace ilexer
{

class ILexer {
public:
    virtual                                              ~ILexer() = default;
    virtual std::vector<std::shared_ptr<itoken::IToken>> test_func() = 0;
};

}



#endif //ILEXER_HPP
