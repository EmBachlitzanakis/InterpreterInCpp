#pragma once
#include "Expression.h"
#include "token.h"
class PrefixExpression : public Expression {
    Token Token;
	std::string Operator;
    Expression* Right;


    // Constructor
    PrefixExpression( ::Token token,  std::string value, Expression* right);

    // Destructor
    ~PrefixExpression() override;

    void expressionNode() override;


    std::string TokenLiteral() const override;

    std::string String() const override;

};
