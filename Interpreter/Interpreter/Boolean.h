#pragma once

#include "Expression.h"
#include "token.h"
class Boolean : public Expression {
    Token Token;
    bool Value;

    // Constructor
    Boolean( ::Token token,  bool value);

    // Destructor
    ~Boolean() override;

    void expressionNode() override;


    std::string TokenLiteral() const override;

    std::string String() const override;

};