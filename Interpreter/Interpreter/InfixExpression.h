#pragma once
#include "Expression.h"
#include "token.h"
class InfixExpression : public Expression {
    Token Token;
    std::string Operator;
    Expression* Right;
    Expression* Left;

    // Constructor
    InfixExpression(::Token token, std::string value, Expression* right, Expression* Left);

    // Destructor
    ~InfixExpression() override;

    void expressionNode() override;


    std::string TokenLiteral() const override;

    std::string String() const override;

};