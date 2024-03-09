
#ifndef ILEXER_HPP
#define ILEXER_HPP

#include "IToken.hpp"

namespace ilexer
{

class ILexer {
public:
    virtual                                    ~ILexer() = default;
    virtual std::vector<func_itoken::tokenPtr> test_func() = 0;
};

}



#endif //ILEXER_HPP
