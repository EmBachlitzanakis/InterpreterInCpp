#pragma once

#include <memory>
#include <string>
    
#include <vector>
#include "Expression.h"
#include "token.h"
class CallExpression : public Expression {
public:
    // Constructor declaration
    CallExpression(Token token, std::unique_ptr<Expression> function, std::vector<std::unique_ptr<Expression>> arguments);

    // Method declarations (implementations will be in the .cpp file)
    void expressionNode() override;
    std::string TokenLiteral() const override;
    std::string String() const override; // Declaration for the simplified String()

    // Getter methods (optional, but good practice)
    const Token& GetToken() const;
    const Expression* GetFunction() const; // Return raw pointer for observation
    const std::vector<std::unique_ptr<Expression>>& GetArguments() const;

private:
    Token token_; // The '(' token
    std::unique_ptr<Expression> function_; // Identifier or FunctionLiteral (owned)
    std::vector<std::unique_ptr<Expression>> arguments_; // Arguments (owned)
};

