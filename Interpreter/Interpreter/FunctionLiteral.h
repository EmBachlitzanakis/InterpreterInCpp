#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Token.h"
#include "Expression.h"
#include "Identifier.h"
#include "BlockStatement.h"

class FunctionLiteral : public Expression {
public:
    Token token;                             // The 'fn' token
    std::vector<std::shared_ptr<Identifier>> parameters;
    std::shared_ptr<BlockStatement> body;

    // Constructor
    FunctionLiteral(
        const Token& token,
        const std::vector<std::shared_ptr<Identifier>>& parameters,
        std::shared_ptr<BlockStatement> body);

    // From Expression interface
    void expressionNode() override;
    std::string TokenLiteral() const override;
    std::string String() const override;
};