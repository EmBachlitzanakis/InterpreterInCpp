#pragma once

#include "Expression.h"
#include "token.h"
class IntegerLiteral : public Expression {
    Token Token;
    int Value;

    // Constructor
    IntegerLiteral( ::Token& token,  int value);

    // Destructor
    ~IntegerLiteral() override;

    void expressionNode() override;


    std::string TokenLiteral() const override;

    std::string String() const override;

};
