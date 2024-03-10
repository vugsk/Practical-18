
#ifndef ILEXER_HPP
#define ILEXER_HPP

#include <memory>
#include <vector>

class IToken;

class ILexer
{
public:
    virtual                                      ~ILexer() = default;
    virtual std::vector<std::shared_ptr<IToken>> lexicalCodeAnalysis() = 0;
};

#endif //ILEXER_HPP
