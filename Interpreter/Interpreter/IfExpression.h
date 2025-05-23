#pragma once

#include <memory>
#include <string>
#include "Token.h"
#include "Expression.h"
#include "BlockStatement.h"

class IfExpression : public Expression {
public:
    Token token;                             // The 'if' token
    std::shared_ptr<Expression> condition;
    std::shared_ptr<BlockStatement> consequence;
    std::shared_ptr<BlockStatement> alternative;

    // Constructor
    IfExpression(const Token& token,
        std::shared_ptr<Expression> condition,
        std::shared_ptr<BlockStatement> consequence,
        std::shared_ptr<BlockStatement> alternative = nullptr);

    // From Expression interface
    void expressionNode() override;
    std::string TokenLiteral() const override;
    std::string String() const override;
};