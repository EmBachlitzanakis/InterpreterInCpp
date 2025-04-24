#include "CallExpression.h"
#include <sstream>
#include <utility>
#include <iostream>
#include <vector>
#include "Expression.h"
#include "token.h"



// Constructor implementation
CallExpression::CallExpression(Token token, std::unique_ptr<Expression> function, std::vector<std::unique_ptr<Expression>> arguments)
    : token_(std::move(token)), function_(std::move(function)), arguments_(std::move(arguments))
{
    // Constructor body is often empty if using member initializer list
}

// Implementation of expressionNode()
void CallExpression::expressionNode() {
    // Implementation is empty as per the Go version
}

// Implementation of TokenLiteral()
std::string CallExpression::TokenLiteral() const {
    return token_.literal;
}

// Implementation of String()
std::string CallExpression::String() const {
    std::stringstream out;

    // Write the function string representation
    if (function_) { // Check if the unique_ptr is not null
        out << function_->String();
    }
    else {
        out << "nullptr"; // Or handle null function as appropriate
    }

    out << "(";

    // Join arguments with ", "
    // Simplified approach similar to the PrefixExpression example's streaming,
    // while still handling multiple arguments with commas.
    for (size_t i = 0; i < arguments_.size(); ++i) {
        if (arguments_[i]) { // Check if the unique_ptr is not null
            out << arguments_[i]->String();
        }
        else {
            out << "nullptr"; // Or handle null arguments as appropriate
        }
        if (i < arguments_.size() - 1) {
            out << ", ";
        }
    }

    out << ")";

    return out.str();
}


// Implementation of Getter methods
const Token& CallExpression::GetToken() const {
    return token_;
}

const Expression* CallExpression::GetFunction() const {
    return function_.get();
}

const std::vector<std::unique_ptr<Expression>>& CallExpression::GetArguments() const {
    return arguments_;
}