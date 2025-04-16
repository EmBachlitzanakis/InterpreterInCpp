#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "Expression.h"
#include "token.h"
#include <string>

class Identifier : public Expression {
public:
    Token Token; 
    std::string Value; 

    // Constructor
    Identifier( ::Token token,  std::string value);

    // Destructor
    ~Identifier() override;

    void expressionNode() override;

    std::string TokenLiteral() const override;

    std::string String() const override;
};

#endif
