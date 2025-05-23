#include "IfExpression.h"
#include <sstream>

IfExpression::IfExpression(const Token& token,
    std::shared_ptr<Expression> condition,
    std::shared_ptr<BlockStatement> consequence,
    std::shared_ptr<BlockStatement> alternative)
    : token(token),
    condition(condition),
    consequence(consequence),
    alternative(alternative) {
}

void IfExpression::expressionNode() {
    // Empty implementation as in the Go code
}

std::string IfExpression::TokenLiteral() const {
    return token.literal;
}

std::string IfExpression::String() const {
    std::ostringstream out;

    out << "if";
    out << condition->String();
    out << " ";
    out << consequence->String();

    if (alternative != nullptr) {
        out << "else ";
        out << alternative->String();
    }

    return out.str();
}=
